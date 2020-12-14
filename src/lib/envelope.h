#ifndef AUDIOFX_ENVELOPE_H
#define AUDIOFX_ENVELOPE_H

#include "clock.h"

namespace afx
{
namespace envelope
{

class Order1st
{
public:
    Order1st(const IClock &clock);
    double operator()(bool pressed);
private:
    const IClock &clock;
    double last;
};

}
}

#endif
