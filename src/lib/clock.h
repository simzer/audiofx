#ifndef AUDIOFX_CLOCK_H
#define AUDIOFX_CLOCK_H

#include <cstdint>

namespace afx
{

struct IClock
{
public:
    double getTime() const;
protected:
    double time;
};

class StepClock : public IClock
{
public:
    StepClock(uint32_t rateInHz = 44100);
    void step();
private:
    double period;
};

}

#endif
