#include "basic.h"

#include <cmath>

using namespace afx;
using namespace afx::wave;

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
