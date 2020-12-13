#ifndef AUDIOFX_GEN_H
#define AUDIOFX_GEN_H

#include "clock.h"

namespace afx
{

class Gen
{
public:
    Gen(const IClock &clock);
    double operator()();
private:
    const IClock &clock;
};

}

#endif
