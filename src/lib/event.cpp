#include "event.h"

#include <cmath>

using namespace afx;

double Event::frequency() const
{
    auto exponential = (note - 69) / 12.0;
    return 440 * pow(2, exponential);
}
