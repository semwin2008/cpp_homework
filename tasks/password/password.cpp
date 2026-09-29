#include "password.h"

bool ValidatePassword(const std::string& password) {
    // size condition
    constexpr size_t MaxPasswordLength = 14;
    constexpr size_t MinPasswordLength = 8;
    if (password.size() > MaxPasswordLength || password.size() < MinPasswordLength) {
        return false;
    }
    // symbols condition
    bool big_letters = false;
    bool small_letters = false;
    bool digits = false;
    bool other_syms = false;
    constexpr char MaxRange = 126;
    constexpr char MinRange = 33;
    for (const char& c : password) {
        // first condition
        if (c > MaxRange || c < MinRange) {
            return false;
        }
        // symbol classes counting
        if ('A' <= c && c <= 'Z') {
            big_letters = true;
        } else if ('a' <= c && c <= 'z') {
            small_letters = true;
        } else if ('0' <= c && c <= '9') {
            digits = true;
        } else {
            other_syms = true;
        }
    }
    // third condition (adding as integers)
    return big_letters + small_letters + digits + other_syms >= 3;
}
