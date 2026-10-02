#include "bitops.h"

constexpr uint8_t Bits = 64;
constexpr uint8_t Bytes = 8;
constexpr uint8_t BitsInByte = 8;
// all bits are 1
constexpr uint64_t BitMask = -1;
// first 8 bits are 1
constexpr uint64_t ByteMask = 255;

uint64_t SwapBytes(uint64_t value) {
    uint64_t result = 0;
    // 64 iterations
    for (int i = 0; i < Bytes; ++i) {
        result <<= BitsInByte;
        result += ByteMask & value;
        value >>= BitsInByte;
    }
    return result;
}

uint64_t ReverseBits(uint64_t value) {
    uint64_t result = 0;
    // 64 iterations
    for (int i = 0; i < Bits; ++i) {
        result <<= 1;
        result += value & 1;
        value >>= 1;
    }
    return result;
}

uint64_t ReverseBitsInBytes(uint64_t value) {
    return ReverseBits(SwapBytes(value));
}

uint64_t SetBits(uint64_t value, uint64_t offset, uint64_t count, uint64_t bits) {
    uint64_t result = value;
    // creating mask of changing bits
    uint64_t mask = BitMask >> offset << offset;
    int64_t rem = Bits - count - offset;
    if (rem < 0) {
        rem = 0;
    }
    mask = mask << rem >> rem;
    // changing bits
    result &= ~mask;
    bits <<= offset;
    bits &= mask;
    result |= bits;
    return result;
}

uint64_t ExtractBits(uint64_t value, uint64_t offset, uint64_t count) {
    // creating mask of changing bits
    uint64_t mask = BitMask >> offset << offset;
    int64_t rem = Bits - count - offset;
    if (rem < 0) {
        rem = 0;
    }
    mask = mask << rem >> rem;
    // changing bits
    value &= mask;
    value >>= offset;
    return value;
}

uint32_t CountSetBits(uint64_t value) {
    uint32_t result = 0;
    for (int i = 0; i < Bits; ++i) {
        result += value & 1;
        value >>= 1;
    }
    return result;
}

uint32_t CountTrailingZeros(uint64_t value) {
    // 64 iterations
    for (int i = 0; i < Bits; ++i) {
        if (value & 1) {
            return i;
        }
        value >>= 1;
    }
    return Bits;
}

uint32_t CountLeadingZeros(uint64_t value) {
    // 64 iterations
    for (int i = Bits - 1; i >= 0; --i) {
        if (value & (1ull << i)) {
            return Bits - i - 1;
        }
    }
    return Bits;
}

uint64_t RotateLeft(uint64_t value, uint32_t shift) {
    shift %= Bits;
    uint64_t result = value << shift;
    uint8_t rem = Bits - shift;
    result |= value >> rem;
    return result;
}

uint64_t RotateRight(uint64_t value, uint32_t shift) {
    shift %= Bits;
    uint64_t result = value >> shift;
    uint8_t rem = Bits - shift;
    result |= value << rem;
    return result;
}

bool IsPowerOfTwo(uint64_t value) {
    return CountSetBits(value) == 1;
}

uint64_t RoundUpToPowerOfTwo(uint64_t value) {
    uint64_t base = 1;
    // 64 iterations
    for (int i = 0; i < Bits; ++i) {
        if (base >= value) {
            return base;
        }
        base <<= 1;
    }
    return 0;
}

uint64_t AlignDown(uint64_t value, uint64_t alignment) {
    return value - value % alignment;
}

uint64_t AlignUp(uint64_t value, uint64_t alignment) {
    return value + (alignment - value % alignment) % alignment;
}
