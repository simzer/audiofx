#include "echo.h"

using namespace afx;
using namespace afx::effect;

Echo::Echo(size_t delay, double level)
    : level(level)
{
    values.resize(delay);
    actIndex = 0;
}

double Echo::operator()(double in)
{
    auto act = values[actIndex] + in;
    values[actIndex] = level * act;
    actIndex = (actIndex + 1) % values.size();
    return act;
}
