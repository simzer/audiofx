#include "envelope.h"

using namespace afx;
using namespace afx::envelope;

Order1st::Order1st(const afx::IClock &clock)
    : clock(clock)
{
    last = 0.0;
}

double Order1st::operator()(bool pressed)
{
    auto act = pressed ? 1.0 : 0.0;
    auto T = 3000.0;
    last = (T * last + act) / (T + 1.0);
    return last;
}
