#ifndef AUDIOFX_FILTER_FILTER_H
#define AUDIOFX_FILTER_FILTER_H

#include "clock.h"

namespace afx
{
namespace filter
{

class Filter
{
public:
    Filter(const IClock &clock) : clock(clock) {}
protected:
    const IClock &clock;
};

}
}

#endif
