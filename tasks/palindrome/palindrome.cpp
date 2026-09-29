#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    size_t left = -1, right = str.size();
    while (right - left > 1) {
        // moving left bound to next non-space symbol
        left--;
        while (left < right && str[left] == ' ') {
            left++;
        }
        // moving right bound to next non-space symbol
        right--;
        while (right > left && str[right] == ' ') {
            right--;
        }
        // if read all the string
        if (left >= right) {
            break
        }
        // found mismatch
        if (str[left] != str[right]) {
            return false;
        }
    }
    // found no mismatch
    return true;
}
