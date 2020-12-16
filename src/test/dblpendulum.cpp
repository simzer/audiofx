#include "clock.h"
#include "sim/dblpendulum.h"
#include "bufferedout.h"
#include "monitor.h"

using namespace afx;

void dblPendulum()
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
