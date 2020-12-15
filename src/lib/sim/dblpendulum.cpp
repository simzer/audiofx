#include "dblpendulum.h"

#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace afx;
using namespace afx::sim;

DblPendulum::DblPendulum(const IClock &clock)
    : clock(clock)
{
    p1.l = 0.001;
    p2.l = 0.00001;
}

std::pair<double, double> DblPendulum::operator()()
{
    static const double g = 9.81;

    auto dT = clock.getStep();

    auto D = p2.f - p1.f;

    auto dw1 = (p1.l*p1.w*p1.w*sin(D)*cos(D) + g*sin(p2.f)*cos(D) + p2.l*p2.w*p2.w*sin(D) - 2*g*sin(p1.f))
        / ( 2*p1.l - p1.l*cos(D)*cos(D) );

    auto dw2 = (-p2.l*p2.w*p2.w*sin(D)*cos(D) + 2*(g*sin(p1.f)*cos(D) - p1.l*p1.w*p1.w*sin(D) - g*sin(p2.f)))
        / ( 2*p2.l - p2.l*cos(D)*cos(D) );

    p1.w += dw1 * dT;
    p2.w += dw2 * dT;

    p1.f += p1.w * dT;
    p2.f += p2.w * dT;

    return { sin(p2.f), cos(p2.f) };
}

DblPendulum::Pendulum::Pendulum()
{
    f = (double)rand() / RAND_MAX;
    w = 0;
}
