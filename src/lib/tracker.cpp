#include "tracker.h"

#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace afx;

Tracker::Tracker(const IClock &clock) : clock(clock) {
    actIndex = 0;
}

void Tracker::loadCsv(const std::string &filename)
{
    std::ifstream in(filename);
    std::string line;
    while (std::getline(in, line)) {
        std::stringstream ss(line);
        double time;
        Event event;
        ss >> time
           >> event.pressed
           >> event.velocity
           >> event.channel
           >> event.note;
        events.emplace_back(time, event);
    }
}

bool Tracker::finished() const
{
    return actIndex >= events.size();
}

void Tracker::operator()()
{
    double actTime = clock.getTime();

    while (actIndex < events.size()
        && events[actIndex].first <= actTime)
    {
        if (onEvent) onEvent(events[actIndex].second);
        actIndex++;
    }
}
