#include "gen.h"

#include <cmath>

using namespace afx;

double Gen::operator()()
{
    static double time = 0;
    time += 1.0/44100;
    double freq = 440;
    return sin(2 * M_PI * time * freq);
}
