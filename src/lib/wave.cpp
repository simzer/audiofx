#include "wave.h"

#include <cmath>

using namespace afx;

Sin::Sin(double freq, const IClock &clock)
    : freq(freq), clock(clock)
{}

void Sin::setFreq(double value)
{
    freq = value;
}

double Sin::operator()()
{
    auto time = clock.getTime();
    return sin(2 * M_PI * time * freq);
}
