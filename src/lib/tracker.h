#ifndef AUDIOFX_TRACKER_H
#define AUDIOFX_TRACKER_H

#include <string>
#include <functional>
#include <vector>

#include "clock.h"
#include "event.h"

namespace afx
{

class Tracker
{
public:
    std::function<void(const Event&)> onEvent;

    Tracker(const IClock &clock);
    void loadCsv(const std::string &filename);
    bool finished() const;
    void operator()();
private:
    const IClock &clock;
    int actIndex;
    std::vector<std::pair<double,Event>> events;
};

}

#endif
