#include "clock.h"
#include "tracker.h"
#include "polysynth.h"
#include "wavegen/fourier.h"
#include "envelope.h"
#include "effect/echo.h"
#include "bufferedout.h"

using namespace afx;

struct Synth : public ISynth
{
    Synth(int channel, double freq, double gain, const IClock &clock)
        : channel(channel),
          gain(gain),
          wave0(freq, 15, clock),
          wave1(freq, 15, clock),
          env(0.005,0.15,0.3,0.5,clock),
          echo(44100 * 0.06, 0.75)
    {}

    double operator()() override {
        auto wave = channel == 0 ? wave0() : wave1();
        auto res = echo(gain * env() * wave);
        return res;
    }

    void setPressed(bool pressed) override {
        env.setPressed(pressed);
    }

    bool isFinished() override {
        return !env.isActive();
    }

private:
    int channel;
    double gain;
    afx::wave::fourier::Triangle wave0;
    afx::wave::fourier::Square wave1;
    afx::effect::Echo echo;
    afx::envelope::ADSR env;
};

void tracker()
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
        auto signal = 5 * synth();
        out << signal << signal;
        clock.step();
    }
}
