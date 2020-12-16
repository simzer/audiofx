#ifndef AUDIOFX_EVENT_H
#define AUDIOFX_EVENT_H

namespace afx
{

struct Event
{
    bool pressed;
    int channel;
    double note;
    double velocity;

    double frequency() const;
};

}

#endif
