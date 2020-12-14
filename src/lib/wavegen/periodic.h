#ifndef AUDIOFX_PERIODICWAVE_H
#define AUDIOFX_PERIODICWAVE_H

#include "clock.h"

namespace afx
{
namespace wave
{

class Periodic
{
public:
    Periodic(double freq, const IClock &clock);
    virtual ~Periodic() {}
    void setFreq(double value);
protected:
    const IClock &clock;
    double freq;
    double periodPos() const;
    double periodPosInRad() const;
};

}
}

#endif
