#include "safe_arithmetic.h"

#include <limits>

bool SafeAdd(int64_t a, int64_t b, int64_t& result) {
    uint64_t ua = a;
    uint64_t ub = b;
    // calculating singed summ without UB danger
    int64_t sum = ua + ub;
    if (b < 0 && sum > a) {
        return false;
    }
    if (b >= 0 && sum < a) {
        return false;
    }
    result = sum;
    return true;
}

bool SafeSubtract(int64_t a, int64_t b, int64_t& result) {
    uint64_t ua = a;
    uint64_t ub = b;
    // calculating singed summ without UB danger
    int64_t sub = ua - ub;
    if (b >= 0 && sub > a) {
        return false;
    }
    if (b < 0 && sub < a) {
        return false;
    }
    result = sub;
    return true;
}

constexpr uint8_t Bits = 64;

bool SafeMultiply(int64_t a, int64_t b, int64_t& result) {
    // corner case
    if (a == INT64_MIN) {
        if (b == 0) {
            result = 0;
            return true;
        }
        if (b == 1) {
            result = a;
            return true;
        }
        return false;
    }
    if (b == INT64_MIN) {
        if (a == 0) {
            result = 0;
            return true;
        }
        if (a == 1) {
            result = b;
            return true;
        }
        return false;
    }
    bool isneg = (a < 0) ^ (b < 0);
    if (a < 0) {
        a = -a;
    }
    if (b < 0) {
        b = -b;
    }
    // 63 iterations
    int64_t mid_res = 0;
    for (int i = 0; i < Bits - 1; ++i) {
        // single bit of b
        int64_t new_b = b & (1ull << i);
        // checking if a * new_b overflows;
        if (new_b) {
            if ((a << i >> i) != a) {
                return false;
            }
            // Trying to multiply partially, bit by bit
            if (!SafeAdd(mid_res, a << i, mid_res)) {
                return false;
            }
        }
    }
    if (isneg) {
        mid_res = -mid_res;
    }
    result = mid_res;
    return true;
}

bool SafeDivide(int64_t a, int64_t b, int64_t& result) {
    if (a == INT64_MIN && b == -1) {
        return false;
    }
    if (b == INT64_MIN && a == -1) {
        return false;
    }
    if (b == 0) {
        return false;
    }
    result = a / b;
    return true;
}
