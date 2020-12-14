#ifndef AUDIOFX_FOURIERWAVE_H
#define AUDIOFX_FOURIERWAVE_H

#include "periodic.h"

#include <cmath>

namespace afx
{
namespace wave
{
namespace fourier
{

template <typename Coefs>
class Generic : public Periodic
{
public:
    Generic(double freq, uint8_t steps, const IClock &clock);
    double operator()();
protected:
    uint8_t steps;
    Coefs coefs;
};

template <typename Coefs>
Generic<Coefs>::Generic(double freq, uint8_t steps, const IClock &clock)
    : Periodic (freq, clock), steps(steps)
{}

template <typename Coefs>
double Generic<Coefs>::operator()()
{
    auto a = 0.0;
    auto b = 0.0;

    auto res = a / 2;
    for (auto i = 1; i <= steps; i++)
    {
        auto x = i * periodPosInRad();
        res += coefs.a(i) * cos(x) + coefs.b(i) * sin(x);
    }
    return res;
}

namespace coef {

struct Sawtooth {
    double a(int i) { return 0; }
    double b(int i) { return 1.0 / i; }
};

struct Triangle {
    double a(int i) { return 0; }
    double b(int i) {
        if (i % 2 == 0) return 0;
        return (8.0 / (M_PI * M_PI)) * pow(-1.0, (i-1.0)/2.0 ) / (i*i);
    }
};

struct Square {
    double a(int i) { return 0; }
    double b(int i) {
        if (i % 2 == 0) return 0;
        return (4.0 / M_PI) * 1.0 / i;
    }
};

struct Clausen {
    double a(int i) { return 0; }
    double b(int i) {
        return 1.0 / (i*i);
    }
};

}

typedef Generic<coef::Sawtooth> Sawtooth;
typedef Generic<coef::Triangle> Triangle;
typedef Generic<coef::Square> Square;
typedef Generic<coef::Clausen> Clausen;

}
}
}

#endif
