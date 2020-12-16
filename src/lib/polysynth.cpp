#include "polysynth.h"

#include <vector>

using namespace afx;

PolySynth::PolySynth(const CreateSynth &createSynth, const IClock &clock)
    : createSynth(createSynth), clock(clock)
{}

void PolySynth::push(const Event &event)
{
    auto key = (event.channel << 16) + event.note;

    auto it = synthMap.find(key);

    if (it == synthMap.end())
        it = synthMap.emplace(key, createSynth(event)).first;

    it->second->setPressed(event.pressed);
}

double PolySynth::operator()()
{
    auto res = 0.0;

    std::vector<int> drop;

    for (auto pair : synthMap)
    {
        auto act = pair.second->operator()();
        res += act;

        if (pair.second->isFinished())
            drop.push_back(pair.first);
    }

    for (auto key : drop) synthMap.erase(key);

    return res;
}
