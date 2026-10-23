#include "image.h"


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

Pixel& Image::At(int i, int j) {
    if (i < 0) i = 0;
    if (i > GetHeight()) i = GetHeight() - 1;
    if (j < 0) j = 0;
    if (j > GetWidth()) j = GetWidth() - 1;
    return matrix_[i][j];
}

void Image::applyConv(const std::vector<std::vector<float>>& kernel) {
    
}
