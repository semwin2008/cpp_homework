#include "elasticTransform.h"
#include "../../exceptions/exceptions.h"
#include "../gaussianBlur/gaussianBlur.h"
#include <random>
#include <vector>
#include <string>


ElasticTransform::ElasticTransform(const FilterArgs& args) {
    if (args.size() < 2 || args.size() > 4) {
        throw BadFilterArgument();
    }
    alpha_ = std::stof(args[0]);
    float sigma = std::stof(args[1]);
    blur_ = GaussianBlur(std::to_string(sigma));
    if (args.size() >= 3) {
        if (args[2] == "nearest" || args[2] == "bilinear") {
            interpolation_mode_ = args[2];
        }else{
            throw BadFilterArgument();
        }
    }
    if (args.size() == 4) {
        int seed = std::stoi(args[3]);
        gen_ = std::mt19937(seed);
    }else{
        gen_ = std::mt19937();
    }
}

void ElasticTransform::apply(Image& image) {
    // generating random shifts
    Image delta_x(image.GetHeight(), image.GetWidth());
    Image delta_y(image.GetHeight(), image.GetWidth());
    std::normal_distribution<float> noise(0.0, alpha_);
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            float dx = noise(gen_), dy = noise(gen_);
            delta_x.At(i, j) = {dx, dx, dx};
            delta_y.At(i, j) = {dy, dy, dy};
        }
    }
    // Blurring shifts
    blur_.apply(delta_x);
    blur_.apply(delta_y);
    // Shifting pixels
    Image tmp(image.GetHeight(), image.GetWidth());
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            if (interpolation_mode_ == "nearest") {
                int from_x = std::round(delta_x.At(i, j).r) + i;
                int from_y = std::round(delta_y.At(i, j).r) + j;
                tmp.At(i, j) = image.At(from_x, from_y);
            } else {
                // bilinear mode
                float real_from_x = delta_x.At(i, j).r + i;
                float real_from_y = delta_y.At(i, j).r + j;
                int corner_x = std::floor(delta_x.At(i, j).r) + i;
                int corner_y = std::floor(delta_y.At(i, j).r) + j;
                tmp.At(i, j) = 
                    image.At(corner_x, corner_y)         * (corner_x + 1 - real_from_x) * (corner_y + 1 - real_from_y) + 
                    image.At(corner_x, corner_y + 1)     * (corner_x + 1 - real_from_x) * (real_from_y - corner_y)     + 
                    image.At(corner_x + 1, corner_y)     * (real_from_x - corner_x)     * (corner_y + 1 - real_from_y) + 
                    image.At(corner_x + 1, corner_y + 1) * (real_from_x - corner_x)     * (real_from_y - corner_y);
            }
        }
    }
    image = std::move(tmp);
}
