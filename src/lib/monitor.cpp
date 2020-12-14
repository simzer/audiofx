#include "monitor.h"

#include <cmath>

using namespace afx;
using namespace afx::monitor;

Volume::Volume(const IClock &clock)
    : clock(clock)
{
    filtered = 0;
}

double Volume::getVolume()
{
    return filtered;
}

void Volume::operator()(double amplitude)
{
    filtered = (fabs(amplitude) + 2200 * filtered) / 2201;
}
