#include "clock.h"
#include "wavegen/basic.h"
#include "wavegen/fourier.h"
#include "envelope.h"
#include "filter/basic.h"
#include "bufferedout.h"
#include "monitor.h"

#include <cmath>

int main(int argc, char *argv[])
{
    afx::StepClock clock(44100);
    auto baseFreq = 80.0;
    afx::wave::fourier::Square wave0(1 * baseFreq, 20, clock);
    afx::wave::fourier::Sawtooth wave1(3 * baseFreq, 20, clock);
    afx::wave::fourier::Triangle wave2(5 * baseFreq, 20, clock);
    afx::wave::fourier::Clausen wave3(7 * baseFreq, 20, clock);
    afx::envelope::ADSR env(1.5,0.5,0.6,1.5,clock);
    afx::filter::LowPass lp(200, clock);
    afx::filter::HighPass hp(200,clock);
    afx::BufferedOutput<int16_t> out(2*1024);
    afx::monitor::Volume vol(clock);

    while (clock.getTime() < .1
          || clock.getTime() < 3
          || vol.getVolume() > 0.001)
    {
        auto press = clock.getTime() < 1;
        auto wave = (1.5 * wave0() + 1.25 * wave1() + 0.75 * wave2() + 0.5 * wave3()) / 4.0;
        auto mono = 0.5 * env(press) * wave;

        auto cutoff = 10 + clock.getTime() * 6000.0 / 2.0;
        lp.setCutoffFreq(cutoff);
        hp.setCutoffFreq(cutoff);
        auto left = lp(mono);
        auto right = hp(mono);

        out << left << right;
        vol(left + right);
        clock.step();
    }
    return 0;
}

/* tested:
afx::wave::Sin
afx::wave::Square
afx::wave::SawTooth
afx::wave::Triangle
afx::wave::Pulse
afx::wave::fourier::Sawtoot
afx::wave::fourier::Square
afx::wave::fourier::Triangle
afx::wave::fourier::Clausen
afx::envelope::ADSR
*/
