#ifndef AUDIOFX_MONITOR_H
#define AUDIOFX_MONITOR_H

#include "clock.h"

namespace afx
{
namespace monitor
{

class Volume
{
public:
    Volume(const IClock &clock);
    double getVolume();
    void operator()(double amplitude);
private:
    const IClock &clock;
    double filtered;
};

}
}

#endif
