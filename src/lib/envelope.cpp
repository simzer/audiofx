#include "envelope.h"

using namespace afx;
using namespace afx::envelope;

ADSR::ADSR(double attack,
           double decay,
           double sustain,
           double release,
           const IClock &clock)
    : attack(attack),
      decay(decay),
      sustain(sustain),
      release(release),
      clock(clock)
{
    startTime = 0;
    lastPressed = false;
    value = 0.0;
}

double ADSR::operator()(bool pressed)
{
    if (pressed && !lastPressed)
        startTime = clock.getTime();

    auto ellapsedTime = clock.getTime() - startTime;

    if (pressed) {
        if (ellapsedTime <= attack) update(attack/4, 1.0);
        else update(decay/4, sustain);
    } else update(release/4, 0.0);

    lastPressed = pressed;

    return value;
}

void ADSR::update(double coef, double target)
{
    if (coef == 0) value = target;
    else {
        auto dt = clock.getStep();
        value = (coef * value + dt * target) / (coef + dt);
    }
}
