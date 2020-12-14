#ifndef AUDIOFX_BASICWAVE_H
#define AUDIOFX_BASICWAVE_H

#include "periodic.h"

namespace afx
{
namespace wave
{

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

class Pulse : public Periodic
{
public:
    Pulse(double freq, double width, const IClock &clock);
    double operator()();
private:
    double width;
};

}
}

#endif
