#include "gen.h"

#include <cmath>

using namespace afx;

Gen::Gen(const IClock &clock)
    : clock(clock)
{}

double Gen::operator()()
{
    auto time = clock.getTime();
    double freq = 440;
    return sin(2 * M_PI * time * freq);
}
