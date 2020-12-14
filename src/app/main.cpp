#include "clock.h"
#include "wavegen/basic.h"
#include "wavegen/fourier.h"
#include "envelope.h"
#include "bufferedout.h"
#include "monitor.h"

#include <cmath>

int main(int argc, char *argv[])
{
    afx::StepClock clock(44100);
    afx::wave::Pulse wave0(200, 0.25, clock);
    afx::envelope::ADSR env(0.01,0.5,0.3,1.0,clock);
    afx::BufferedOutput<int16_t> out(2*1024);
    afx::monitor::Volume vol(clock);

    while (clock.getTime() < .1 || vol.getVolume() > 0.001)
    {
        auto press = clock.getTime() < 1;
        auto sample = env(press) * wave0();
        out << sample << sample;
        vol(sample);
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
