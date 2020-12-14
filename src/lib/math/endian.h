#ifndef AUDIOFX_MATH_ENDIAN_H
#define AUDIOFX_MATH_ENDIAN_H

#include "bits.h"

namespace afx
{
namespace math
{

#pragma pack(push, 1)

template <typename LEType>
struct BigEndian {
	typedef LEType ValueType;
	ValueType raw;
	BigEndian() { raw = 0; }
	BigEndian(const BigEndian &other) { raw = other.raw; }
	BigEndian(ValueType value) { *this = value; }
	void operator=(ValueType value) { raw = swapBytes(value); }
	operator ValueType() const { return swapBytes(raw); }
};

typedef BigEndian<uint16_t> beint16;
typedef BigEndian<uint32_t> beint32;
typedef BigEndian<uint64_t> beint64;

typedef BigEndian<uint16_t> beuint16;
typedef BigEndian<uint32_t> beuint32;
typedef BigEndian<uint64_t> beuint64;

#pragma pack(pop)

}
}

#endif
