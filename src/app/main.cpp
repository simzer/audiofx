#include "clock.h"
#include "gen.h"
#include "bufferedout.h"

int main(int argc, char *argv[])
{
    afx::StepClock clock(44100);
    afx::Gen gen(clock);
    afx::BufferedOutput<int16_t> out(2*1024);
    while (1)
    {
        auto sample = gen();
        out << sample << sample;
        clock.step();
    }
    return 0;
}
