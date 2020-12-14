#include "clock.h"
#include "basicwave.h"
#include "fourierwave.h"
#include "bufferedout.h"

#include <cmath>

int main(int argc, char *argv[])
{
    afx::StepClock clock(44100);
    afx::FourierSquare wave0(180, 30, clock);
    afx::Square wave1(180, clock);
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
