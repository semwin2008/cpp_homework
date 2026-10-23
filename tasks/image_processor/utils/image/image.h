#pragma once


#include <vector>


struct Pixel{
    Pixel() = default;
    Pixel(float value) : r(value), g(value), b(value) {}
    Pixel(float r, float g, float b) : r(r), g(g), b(b) {}

    float r = 0;
    float g = 0;
    float b = 0;
};


class Image{
public:
    Image() = default;
    Image(int n, int m) : matrix_(std::vector<std::vector<Pixel>> (n, std::vector<Pixel>(m))) {}
    Pixel& At(const size_t i, const size_t j) {
        return matrix_[i][j];
    }
    size_t GetHeight() const {
        return matrix_.size();
    }
    size_t GetWidth() const {
        if (matrix_.empty()) return 0;
        return matrix_[0].size();
    }

private:
    std::vector<std::vector<Pixel>> matrix_;
};

