#include "clock.h"

using namespace afx;

double IClock::getTime() const
{
    return time;
}

StepClock::StepClock(uint32_t rateInHz)
{
    time = 0;
    period = 1.0 / rateInHz;
}

void StepClock::step()
{
    time += period;
}
