#include "basic.h"

#include <cmath>
#include <iostream>

using namespace afx;
using namespace afx::filter;

LowPass::LowPass(double cutoffFreq, const IClock &clock)
    : Filter(clock)
{
    setCutoffFreq(cutoffFreq);
    value = 0.0;
}

void LowPass::setCutoffFreq(double value)
{
    RC = 1.0 / (2.0 * M_PI * value);
}

double LowPass::operator()(double in)
{
    auto step = clock.getStep();
    auto alpha = step / (RC + step);
    value = alpha * in + (1.0 - alpha) * value;
    return value;
}

HighPass::HighPass(double cutoffFreq, const IClock &clock)
    : Filter(clock)
{
    setCutoffFreq(cutoffFreq);
    value = 0.0;
    lastIn = 0.0;
}

void HighPass::setCutoffFreq(double value)
{
    RC = 1.0 / (2.0 * M_PI * value);
}

double HighPass::operator()(double in)
{
    auto step = clock.getStep();
    auto alpha = RC / (RC + step);
    value = alpha * value + alpha * (in - lastIn);
    lastIn = in;
    return value;
}
