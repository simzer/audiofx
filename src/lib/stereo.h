#ifndef AUDIOFX_STEREO_H
#define AUDIOFX_STEREO_H

#include <utility>

namespace afx
{

template <typename T>
class Stereo
{
public:
    typedef std::pair<double, double> Value;

    template <typename ... Args>
    Stereo(Args ... args)
        : left(args...), right(args...)
    {}
    Value operator()(const Value &in)
    {
        return { left(in.first), right(in.second) };
    }
private:
    T left;
    T right;
};

}

#endif
