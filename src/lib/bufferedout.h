#ifndef AUDIOFX_BUFFEREDOUT_H
#define AUDIOFX_BUFFEREDOUT_H

#include <cstdint>
#include <vector>
#include <iostream>
#include <limits>

namespace afx
{

template <typename T>
class BufferedOutput
{
public:
    BufferedOutput(uint32_t size = 1024)
        : maxSize(size)
    {
        buffer.reserve(maxSize);
    }

    BufferedOutput &operator<<(double value)
    {
        value = std::max(-1.0, std::min(value, 1.0));
        auto sample = (T)(value * std::numeric_limits<T>::max());
        buffer.push_back(sample);
        if (buffer.size() == maxSize)
        {
            std::cout.write((const char*)buffer.data(),
                            sizeof(T) * buffer.size());
            buffer.clear();
        }
        return *this;
    }

private:
    uint32_t maxSize;
    std::vector<T> buffer;
};

}

#endif
