#include "clock.h"
#include "wave.h"
#include "bufferedout.h"

#include <cmath>

int main(int argc, char *argv[])
{
    afx::StepClock clock(44100);
    afx::Pulse wave0(220, 0.6, clock);
    afx::SawTooth wave1(220 * 3/2.0, clock);
    afx::SawTooth wave2(220 * 5/4.0, clock);
    afx::BufferedOutput<int16_t> out(2*1024);
    while (1)
    {
//        auto sample = (wave0() + wave1() + wave2()) / 3;
        auto sample = wave0() / 3;
        out << sample << sample;
        clock.step();
    }
    return 0;
}
