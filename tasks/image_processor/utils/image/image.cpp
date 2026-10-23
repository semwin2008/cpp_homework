#include "utils/image/image.h"


Pixel Pixel::operator+(const Pixel& rhs) const {
    return Pixel{
        r + rhs.r,
        g + rhs.g,
        b + rhs.b
    };
}

Pixel Pixel::operator-(const Pixel& rhs) const {
    return Pixel{
        r - rhs.r,
        g - rhs.g,
        b - rhs.b
    };
}

Pixel Pixel::operator*(const Pixel& rhs) const {
    return Pixel{
        r * rhs.r,
        g * rhs.g,
        b * rhs.b
    };
}
