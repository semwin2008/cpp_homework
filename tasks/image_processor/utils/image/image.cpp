#include "image.h"
#include <iostream>
#include "../exceptions/exceptions.h"
#include <algorithm>


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
    if (i >= GetHeight()) i = GetHeight() - 1;
    if (j < 0) j = 0;
    if (j >= GetWidth()) j = GetWidth() - 1;
    return matrix_[i][j];
}

void Pixel::Clamp(float a, float bb) {
    r = std::min(bb, std::max(a, r));
    g = std::min(bb, std::max(a, g));
    b = std::min(bb, std::max(a, b));
}


void Image::applyConv(const std::vector<std::vector<float>>& kernel) {
    if (kernel.empty()) {
        throw EmptyKernelException("kernel cannot be empty");
    }
    Image tmp(matrix_);
    int distance = kernel.size() / 2;
    for (int i = 0; i < GetHeight(); ++i) {
        for (int j = 0; j < GetWidth(); ++j) {
            At(i, j) = 0;
            for (int k = 0; k < kernel.size(); ++k) {
                for (int t = 0; t < kernel[0].size(); ++t) {
                    int from_x = i + k - distance;
                    int from_y = j + t - distance;
                    At(i, j) = At(i, j) + (tmp.At(from_x, from_y) * kernel[k][t]);
                }
            }
        }
    }
}


void Image::NormalizeValues() {
    for (size_t i = 0; i < GetHeight(); ++i) {
        for (size_t j = 0; j < GetWidth(); ++j) {
            At(i, j).Clamp(0.0, 1.0);
        }
    }
}
