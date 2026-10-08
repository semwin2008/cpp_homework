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

private:
    std::vector<std::vector<Pixel>> matrix;
};

