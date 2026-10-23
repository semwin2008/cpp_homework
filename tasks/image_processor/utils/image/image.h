#pragma once

#include <vector>
#include <cstdint>


const uint8_t PIXEL_MAX_VALUE = 255;
const float SCALE_TO_FLOAT = 1.0f / PIXEL_MAX_VALUE;

struct Pixel{
    float r = 0;
    float g = 0;
    float b = 0;

    Pixel() = default;
    Pixel(float value) : r(value), g(value), b(value) {}
    // Normalized input
    Pixel(float r, float g, float b) : r(r), g(g), b(b) {}
    // Unnormalized input
    Pixel(uint8_t r, uint8_t g, uint8_t b) : 
        r(r * SCALE_TO_FLOAT), 
        g(g * SCALE_TO_FLOAT), 
        b(b * SCALE_TO_FLOAT) {}

    // Arithmetics
    Pixel operator+(const Pixel& rhs) const;
    Pixel operator-(const Pixel& rhs) const;
    Pixel operator*(const Pixel& rhs) const;
};


class Image{
public:
    Image() = default;
    Image(int n, int m) : matrix_(std::vector<std::vector<Pixel>> (n, std::vector<Pixel>(m))) {}
    Pixel& At(const size_t i, const size_t j){
        return matrix_[i][j];
    }
    Pixel At(const size_t i, const size_t j) const {
        return matrix_[i][j];
    }
    Pixel& At(const int i, const int j);
    size_t GetHeight() const {
        return matrix_.size();
    }
    size_t GetWidth() const {
        if (matrix_.empty()) return 0;
        return matrix_[0].size();
    }
    void applyConv(const std::vector<std::vector<float>>& kernel);

private:
    std::vector<std::vector<Pixel>> matrix_;
};

