#ifndef AUDIOFX_WAVE_H
#define AUDIOFX_WAVE_H

#include "clock.h"

namespace afx
{

class Sin
{
public:
    Sin(double freq, const IClock &clock);
    void setFreq(double value);
    double operator()();
private:
    const IClock &clock;
    double freq;
};

}

#endif
