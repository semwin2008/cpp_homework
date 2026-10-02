#include "varint.h"

size_t DecodeVarint(const uint8_t* data, size_t size, uint64_t& result) {
    constexpr uint8_t ValueSize = 7;
    // Every bit is 1 except the last
    constexpr uint8_t ValueMask = (1 << ValueSize) - 1;
    // Invalid input
    constexpr size_t MaxSize = 10;
    if (size > MaxSize) {
        return 0;
    }
    // how many bits can we read in the last byte without 64-bit integer overflow
    constexpr uint8_t MaxBitsInLastByte = 64 - ValueSize * (MaxSize - 1);
    uint64_t result_tmp = 0;
    uint64_t base = 1;
    for (size_t i = 0; i < size; ++i) {
        uint8_t value = data[i];
        // last byte
        if (i + 1 == MaxSize) {
            // Input is too large for a 64-bit integer
            if (value >= (1 << MaxBitsInLastByte)) {
                return 0;
            }
        }
        // last bit is 0
        if ((value & ValueMask) == value) {
            result_tmp += base * value;
            result = result_tmp;
            return i + 1;
        }
        value &= ValueMask;
        result_tmp += value * base;
        base <<= ValueSize;
    }
    // corner case: no ending detected;
    return 0;
}
