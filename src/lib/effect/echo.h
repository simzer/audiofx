#ifndef AUDIOFX_EFFECT_ECHO_H
#define AUDIOFX_EFFECT_ECHO_H

#include "clock.h"

#include <vector>

namespace afx
{
namespace effect
{

class Echo
{
public:
    Echo(size_t delay, double level);
    double operator()(double in);
protected:
    double level;
    size_t actIndex;
    std::vector<double> values;
};

}
}

#endif
