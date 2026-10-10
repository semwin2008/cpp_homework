#pragma once


#include <vector>


class Pixel{
public:
    Pixel() = default;

private:
    float r = 0;
    float g = 0;
    float b = 0;
};


class Image{
public:
    Image() = default;
    Image(int n, int m) : matrix(std::vector<std::vector<Pixel>> (n, std::vector<Pixel>(m))) {}
    Pixel& At(const size_t i, const size_t j) {
        return matrix[i][j];
    }

private:
    std::vector<std::vector<Pixel>> matrix;
};

