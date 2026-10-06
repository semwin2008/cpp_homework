#include "fp16.h"
#include <cmath>

constexpr uint8_t Bits16 = 16;
constexpr uint8_t Exp16 = 5;
constexpr uint8_t Man16 = 10;
constexpr uint8_t Exp16Bias = 15;
constexpr float ManNorm = 1024.0f;

float ConvertFloat16ToFloat(uint16_t float16_bits) {
    // parsing float16 bits into parts (sgn, mat, exp)
    uint32_t input = static_cast<uint32_t>(float16_bits);
    uint32_t sgn = input >> (Bits16 - 1);
    input ^= sgn << (Bits16 - 1);
    uint32_t exp = input >> (Bits16 - 1 - Exp16);
    uint32_t man = input ^ (exp << (Bits16 - 1 - Exp16));
    // corner case with 0
    if (exp == 0 && man == 0) {
        return sgn ? -0.0f : 0.0f;
    }
    // subnormal value case
    if (exp == 0) {
        int shift = 0;
        while ((man & (1 << Man16)) == 0 && man != 0) {
            man <<= 1;
            shift++;
        }
        exp = 1 - shift;
        man &= (1 << Man16) - 1;
    }
    // inf | NaN value cases
    if (exp == (1 << Exp16) - 1) {
        if (man == 0) {
            return sgn ? -INFINITY : INFINITY;
        } else {
            return NAN;
        }
    }
    // subtracting float16 bias from exp
    int32_t exp32 = static_cast<int32_t>(exp) - Exp16Bias;
    // casting mantissa to float
    float mantissa_value = 1.0f + static_cast<float>(man) / ManNorm;
    // computing result value
    float result = std::ldexp(mantissa_value, exp32);
    return sgn ? -result : result;
}
