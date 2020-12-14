#include "clock.h"

using namespace afx;

IClock::IClock()
{
    time = 0;
    dt = 0;
}

double IClock::getTime() const
{
    return time;
}

double IClock::getStep() const
{
    return dt;
}

void IClock::setTime(double value)
{
    dt = value - time;
    time = value;
}

StepClock::StepClock(uint32_t rateInHz)
{
    period = 1.0 / rateInHz;
}

void StepClock::step()
{
    setTime(getTime() + period);
}
