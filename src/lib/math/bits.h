#ifndef AUDIOFX_MATH_BITS_H
#define AUDIOFX_MATH_BITS_H

#include <cstdint>

namespace afx
{
namespace math
{

inline uint64_t swapBytes(uint64_t value)
{
	return
	      (value & 0xFF00000000000000ull) >> 56
	    | (value & 0x00FF000000000000ull) >> 40
	    | (value & 0x0000FF0000000000ull) >> 24
	    | (value & 0x000000FF00000000ull) >> 8
	    | (value & 0x00000000FF000000ull) << 8
	    | (value & 0x0000000000FF0000ull) << 24
	    | (value & 0x000000000000FF00ull) << 40
	    | (value & 0x00000000000000FFull) << 56;
}

inline int64_t swapBytes(int64_t value) {
	return (int64_t)swapBytes((uint64_t)value);
}

inline uint32_t swapBytes(uint32_t value)
{
	return (value & 0xFF000000) >> 24
	     | (value & 0x00FF0000) >> 8
	     | (value & 0x0000FF00) << 8
	     | (value & 0x000000FF) << 24;
}

inline int32_t swapBytes(int32_t value) {
	return (int32_t)swapBytes((uint32_t)value);
}

inline uint16_t swapBytes(uint16_t value)
{
	return (value & 0xFF00) >> 8
	     | (value & 0x00FF) << 8;
}

inline int16_t swapBytes(int16_t value) {
	return (int16_t)swapBytes((uint16_t)value);
}

}
}

#endif
