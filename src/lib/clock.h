#ifndef AUDIOFX_CLOCK_H
#define AUDIOFX_CLOCK_H

#include <cstdint>

namespace afx
{

struct IClock
{
public:
    IClock();
    virtual ~IClock() {}
    double getTime() const;
    double getStep() const;
protected:
    void setTime(double value);
private:
    double dt;
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
