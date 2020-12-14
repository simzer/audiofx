#ifndef AUDIOFX_FOURIERWAVE_H
#define AUDIOFX_FOURIERWAVE_H

#include "periodicwave.h"

#include <cmath>

namespace afx
{

template <typename Coefs>
class Fourier : public Periodic
{
public:
    Fourier(double freq, uint8_t steps, const IClock &clock);
    double operator()();
protected:
    uint8_t steps;
    Coefs coefs;
};

template <typename Coefs>
Fourier<Coefs>::Fourier(double freq, uint8_t steps, const IClock &clock)
    : Periodic (freq, clock), steps(steps)
{}

template <typename Coefs>
double Fourier<Coefs>::operator()()
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

struct SawToothCoefs {
    double a(int i) { return 0; }
    double b(int i) { return 1.0 / i; }
};

struct TriangleCoefs {
    double a(int i) { return 0; }
    double b(int i) {
        if (i % 2 == 0) return 0;
        return (8.0 / (M_PI * M_PI)) * pow(-1.0, (i-1.0)/2.0 ) / (i*i);
    }
};

struct SquareCoefs {
    double a(int i) { return 0; }
    double b(int i) {
        if (i % 2 == 0) return 0;
        return (4.0 / M_PI) * 1.0 / i;
    }
};

typedef Fourier<SawToothCoefs> FourierSawTooth;
typedef Fourier<TriangleCoefs> FourierTriangle;
typedef Fourier<SquareCoefs> FourierSquare;

}

#endif
