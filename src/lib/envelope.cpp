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
    pressed = false;
    value = 0.0;
}

void ADSR::setPressed(bool pressed)
{
    if (pressed && !this->pressed)
        startTime = clock.getTime();

    this->pressed = pressed;
}

bool ADSR::isActive() const
{
    return pressed || (value > 0.01);
}

double ADSR::operator()()
{
    auto ellapsedTime = clock.getTime() - startTime;

    if (pressed) {
        if (ellapsedTime <= attack) update(attack/4, 1.0);
        else update(decay/4, sustain);
    } else update(release/4, 0.0);

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
