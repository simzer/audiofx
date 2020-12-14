#ifndef AUDIOFX_MATH_INT_H
#define AUDIOFX_MATH_INT_H

namespace afx
{
namespace math
{

inline double floor(double x)
{
    int i = (int)x;
    return (double)(i - ( i > x ));
}

}
}

#endif
