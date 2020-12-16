#ifndef AUDIOFX_ENVELOPE_H
#define AUDIOFX_ENVELOPE_H

#include "clock.h"

namespace afx
{
namespace envelope
{

class ADSR
{
public:
    ADSR(double attack,
         double decay,
         double sustain,
         double release,
         const IClock &clock);
    void setPressed(bool pressed);
    bool isActive() const;
    double operator()();
private:
    const IClock &clock;
    bool pressed;
    double startTime;
    double attack;
    double decay;
    double sustain;
    double release;
    double value;
    void update(double coef, double target);
};

}
}

#endif
