#ifndef AUDIOFX_WAVE_H
#define AUDIOFX_WAVE_H

#include "clock.h"

namespace afx
{

class Periodic
{
public:
    Periodic(double freq, const IClock &clock);
    void setFreq(double value);
protected:
    const IClock &clock;
    double freq;
    double periodPos() const;
    double periodPosInRad() const;
};

class Sin : public Periodic
{
public:
    using Periodic::Periodic;
    double operator()();
};

class SawTooth : public Periodic
{
public:
    using Periodic::Periodic;
    double operator()();
};

class Square : public Periodic
{
public:
    using Periodic::Periodic;
    double operator()();
};

class Triangle : public Periodic
{
public:
    using Periodic::Periodic;
    double operator()();
};

}

#endif
