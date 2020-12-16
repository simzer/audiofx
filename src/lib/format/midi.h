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

static constexpr uint32_t chunkType(const char *s) {
    return (uint32_t)s[0] | (s[1] << 8u) | (s[2] << 16u) | (s[3] << 24u);
}

#pragma pack(push, 1)

struct Chunk
{
    enum class Type : uint32_t {
        header = chunkType("MThd"),
        track = chunkType("MTrk")
    };

    Type type;
    math::beuint32 dataLength;
    char *begin() { return (char*)(this + 1); }
    char *end() { return begin() + dataLength; }
    Chunk &next() { return *(Chunk*)end(); }
};

static_assert (sizeof(Chunk) == 8, "Chunk size missmatch");

struct HeaderData
{
    enum class Format : uint16_t {
        single = 0 << 8,
        simultaneous = 1 << 8,
        sequential = 2 << 8
    };

    Format format;
    math::beuint16 numOfTracks;
    math::beuint16 division;
};

#pragma pack(pop)

class Parser
{

};

}
}
}

#endif
