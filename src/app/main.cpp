#include "clock.h"
#include "stereo.h"
#include "tracker.h"
#include "polysynth.h"
#include "wavegen/basic.h"
#include "wavegen/fourier.h"
#include "envelope.h"
#include "filter/basic.h"
#include "effect/echo.h"
#include "sim/dblpendulum.h"
#include "bufferedout.h"
#include "monitor.h"

#include <cmath>

using namespace afx;

void test0();
void test1();
void test2();

int main(int argc, char *argv[])
{
    test2();
    return 0;
}

void test2()
{
    struct Synth : public ISynth
    {
        Synth(double freq, double gain, const IClock &clock)
            : gain(gain),
              wave(freq, 15, clock),
              env(0.01,0.5,0.75,1.5,clock)
        {}

        double operator()() override {
            auto res = gain * env() * wave();
            return res;
        }

        void setPressed(bool pressed) override {
            env.setPressed(pressed);
        }

        bool isFinished() override {
            return !env.isActive();
        }

    private:
        double gain;
        afx::wave::fourier::Triangle wave;
        afx::envelope::ADSR env;
    };

    afx::StepClock clock(44100);
    afx::Tracker tracker(clock);
    afx::PolySynth synth([&](auto &event) {
        return std::make_shared<Synth>(event.frequency(), event.velocity, clock);
    }, clock);
    afx::BufferedOutput<int16_t> out(2*1024);

    tracker.loadCsv("the_entertainer.csv");
    tracker.onEvent = [&](auto &event) {
        synth.push(event);
    };

    while (!tracker.finished())
    {
        tracker();
        auto signal = 5 * synth();
        out << signal << signal;
        clock.step();
    }
}

void test1()
{
    afx::StepClock clock(44100);
    afx::sim::DblPendulum sim(clock);
    afx::BufferedOutput<int16_t> out(2*1024);
    afx::monitor::Volume vol(clock);

    while (clock.getTime() < 100)
    {
        auto val = sim();
        out << val.first << val.second;
        vol(val.first + val.second);
        clock.step();
    }
}

void test0()
{
    afx::StepClock clock(44100);
    auto baseFreq = 80.0;
    afx::wave::Sin lfo0(0.05, clock);
    afx::wave::Sin lfo1(15, clock);
    afx::wave::fourier::Square wave0(1 * baseFreq, 20, clock);
    afx::wave::fourier::Sawtooth wave1(3 * baseFreq, 20, clock);
    afx::wave::fourier::Triangle wave2(5 * baseFreq, 20, clock);
    afx::wave::fourier::Clausen wave3(7 * baseFreq, 20, clock);
    afx::envelope::ADSR env(1.5/15,0.5,0.6,1.5,clock);
    afx::filter::LowPass lp(200, clock);
    afx::filter::HighPass hp(200,clock);
    afx::Stereo<afx::effect::Echo> echo(44100 * 1.2, 0.45);
    afx::BufferedOutput<int16_t> out(2*1024);
    afx::monitor::Volume vol(clock);

    while (clock.getTime() < .1
          || clock.getTime() < 3
          || vol.getVolume() > 0.001)
    {
        auto amp = 1 + 0.25 * lfo0() * lfo1();
        auto press = clock.getTime() < 1;
        auto wave = (1.5 * wave0() + 1.25 * wave1() + 0.75 * wave2() + 0.5 * wave3()) / 4.0;
        env.setPressed(press);
        auto mono = amp * 0.5 * env() * wave;

        auto cutoff = 10 + clock.getTime() * 6000.0 / 2.0;
        lp.setCutoffFreq(cutoff);
        hp.setCutoffFreq(cutoff);
        auto left = lp(mono);
        auto right = hp(mono);

        auto [l, r] = echo({ left, right });

        out << l << r;
        vol(l + r);
        clock.step();
    }
}
