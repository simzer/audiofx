#ifndef AUDIOFX_POLYSYNTH_H
#define AUDIOFX_POLYSYNTH_H

#include "event.h"
#include "clock.h"

#include <functional>
#include <memory>
#include <map>

namespace afx
{

struct ISynth
{
    virtual ~ISynth() {}
    virtual double operator()() = 0;
    virtual void setPressed(bool value) = 0;
    virtual bool isFinished() = 0;
};
typedef std::shared_ptr<ISynth> ISynthPtr;

class PolySynth
{
public:
    typedef std::function<ISynthPtr(const Event&)> CreateSynth;

    CreateSynth createSynth;

    PolySynth(const CreateSynth &createSynth, const IClock &clock);
    void push(const Event &event);
    double operator()();

private:
    const IClock &clock;
    std::map<int, ISynthPtr> synthMap;
};


}

#endif
