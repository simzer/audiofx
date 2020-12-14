#ifndef AUDIOFX_FILTER_BASIC_H
#define AUDIOFX_FILTER_BASIC_H

#include "filter.h"

namespace afx
{
namespace filter
{

class LowPass : public Filter
{
public:
    LowPass(double cutoffFreq, const IClock &clock);
    void setCutoffFreq(double value);
    double operator()(double in);
private:
    double RC;
    double value;
};

class HighPass : public Filter
{
public:
    HighPass(double cutoffFreq, const IClock &clock);
    void setCutoffFreq(double value);
    double operator()(double in);
private:
    double RC;
    double value;
    double lastIn;
};

}
}

#endif
