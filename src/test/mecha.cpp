#include "clock.h"
#include "wavegen/basic.h"
#include "sim/mecha.h"
#include "tracker.h"
#include "polysynth.h"
#include "bufferedout.h"
#include "monitor.h"

using namespace afx;

struct Synth : public ISynth
{
    Synth(int channel, double freq, double gain, const IClock &clock)
        : vol(clock),
          string(50, { 0, 0, 0}, 2*gain, clock)
    {
        pressed = false;
        string.material.dump = 0.05 / freq;
        string.material.mass = 0.01 / freq;
        string.material.spring = 27 * freq;
    }

    double operator()() override {
        auto res = string() / 10000;
        vol(res);
        return res;
    }

    void setPressed(bool pressed) override {
        if (!this->pressed && pressed)
            string.pluck();
        this->pressed = pressed;
    }

    bool isFinished() override {
        return !pressed && vol.getVolume() < 0.01;
    }

    bool pressed;
    afx::sim::mecha::String string;
    afx::monitor::Volume vol;
};

void mecha()
{
    afx::StepClock clock(44100);
    afx::Tracker tracker(clock);
    afx::PolySynth synth([&](auto &event) {
        return std::make_shared<Synth>
                (event.channel, event.frequency(), event.velocity, clock);
    }, clock);
    afx::BufferedOutput<int16_t> out(2*1024);

    tracker.loadCsv("the_entertainer.csv");
    tracker.onEvent = [&](auto &event) {
        synth.push(event);
    };

    while (!tracker.finished() || synth.isActive())
    {
        tracker();
        auto signal = 2 * synth();
        out << signal << signal;
        clock.step();
    }
}
