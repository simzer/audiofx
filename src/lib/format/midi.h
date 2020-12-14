#ifndef AUDIOFX_FORMAT_MIDI_H
#define AUDIOFX_FORMAT_MIDI_H

#include <cstdint>

#include "math/endian.h"

namespace afx
{
namespace format
{
namespace midi
{

#pragma pack(push, 1)

struct Chunk
{
    typedef char Type[4];
    Type type;
    math::beuint32 dataLength;
    char *begin() { return (char*)(this + 1); }
    char *end() { return begin() + dataLength; }
    Chunk &next() { return *(Chunk*)end(); }
};

static_assert (sizeof(Chunk) == 8, "Chunk size missmatch");

#pragma pack(pop)

class Parser
{

};

}
}
}

#endif
