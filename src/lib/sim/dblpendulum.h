#ifndef AUDIOFX_SIM_DBLPENDULUM_H
#define AUDIOFX_SIM_DBLPENDULUM_H

#include <utility>

#include "clock.h"

namespace afx
{
namespace sim
{

class DblPendulum
{
public:
    DblPendulum(const IClock &clock);
    std::pair<double,double> operator()();

private:

    struct Pendulum
    {
        double l; // lenght
        double f; // angle
        double w; // angular speed
        Pendulum();
    };

    const IClock &clock;
    Pendulum p1;
    Pendulum p2;
};

}
}

#endif
