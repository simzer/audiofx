#include "clock.h"
#include "wavegen/basic.h"
#include "sim/mecha.h"
#include "bufferedout.h"
#include "monitor.h"

using namespace afx;

void mecha()
{
    afx::StepClock clock(44100);
    afx::sim::mecha::Material material(0.0003, 30000, 0.00002);
    afx::sim::mecha::String string(50, material, clock);
    afx::BufferedOutput<int16_t> out(2*1024);
    afx::monitor::Volume vol(clock);

    while (clock.getTime() < 1 || vol.getVolume() > 0.002)
    {
        auto val = string();
        out << val << val;
        vol(val);
        clock.step();
    }
}
