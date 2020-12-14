#include "trig.h"

#include <cmath>
#include <functional>
#include <array>

using namespace afx;
using namespace afx::math;

template<int N>
struct Table
{
    std::array<double, N> values;

    Table(std::function<double(double)> gen)
    {
        for (auto i = 0; i < N; ++i)
        {
            auto x = 2.0 * pi * i / N;
            values[i] = gen(x);
        }
    }

    double operator()(double x) {
        int i = N * x / (2 * pi);
        i = i % N;
        return values[i];
    }
};

double afx::math::sin(double x)
{
    static auto lookup = Table<64*1024>([](double x) { return ::sin(x); });
    return lookup(x);
}

double afx::math::cos(double x)
{
    static auto lookup = Table<64*1024>([](double x) { return ::cos(x); });
    return lookup(x);
}
