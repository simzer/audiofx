#include <iostream>

#include "gen.h"

int main(int argc, char *argv[])
{
    afx::Gen gen;
    while (1) {
        int16_t buf[2*1024];
        for (auto i = 0; i < 1024; i++) {
            auto sample = (int16_t)(0.75 * gen() * 0x7FFF);
            buf[2*i] = sample;
            buf[2*i+1] = sample;
        }
        std::cout.write((const char*)buf, sizeof(buf));
    }
    return 0;
}
