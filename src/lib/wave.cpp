#include "wave.h"

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

double Sin::operator()()
{
    return sin(periodPosInRad());
}

double SawTooth::operator()()
{
    auto p = periodPos();
    return 2 * ( p - floor(0.5 + p) );
}

double Square::operator()()
{
    return periodPos() >= 0.5 ? 1 : -1;
}

double Triangle::operator()()
{
    auto p = periodPos();
    auto saw = 2 * ( p - floor(0.5 + p) );
    return 2 * fabs(saw) - 1;
}

Pulse::Pulse(double freq, double width, const IClock &clock)
    : Periodic(freq, clock),
      width(width)
{}

double Pulse::operator()()
{
    return periodPos() < width ? 1 : -1;
}
