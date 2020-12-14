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
    afx::wave::fourier::Triangle wave0(180, 30, clock);
    afx::envelope::Order1st env(clock);
    afx::BufferedOutput<int16_t> out(2*1024);
    afx::monitor::Volume vol(clock);

    while (clock.getTime() < 1 || vol.getVolume() > 0.001)
    {
        auto press = clock.getTime() < 1;
        auto sample = env(press) * wave0();
        out << sample << sample;
        vol(sample);
        clock.step();
    }
    return 0;
}
