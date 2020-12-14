#include "periodicwave.h"

#include <cmath>

using namespace afx;

Periodic::Periodic(double freq, const IClock &clock)
    : freq(freq), clock(clock)
{}

void Periodic::setFreq(double value)
{
    freq = value;
}

double Periodic::periodPos() const
{
    auto time = clock.getTime();
    auto absPos = time * freq;
    return absPos - floor(absPos);
}

double Periodic::periodPosInRad() const
{
    return 2 * M_PI * periodPos();
}
