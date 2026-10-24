#include "../../exceptions/exceptions.h"
#include "gaussianBlur.h"
#include <cmath>


GaussianBlur::GaussianBlur(const FilterArgs& args) {
    if (args.size() != 1) {
        throw BadFilterArgumentException("gaussian blur takes exactly 1 arg (sigma)");
    }
    sigma_ = std::stof(args[0]);
}

void GaussianBlur::apply(Image& image) {
    size_t distance = static_cast<size_t>(sigma_ * 3);
    size_t kernel_size = 2 * distance + 1;
    std::vector<std::vector<float>> kernel(kernel_size, std::vector<float>(kernel_size));
    for (int i = 0; i < kernel_size; ++i) {
        for (int j = 0; j < kernel_size; ++j) {
            int x = i - distance;
            int y = j - distance;
            kernel[i][j] = expf(- (x * x + y * y) / (2 * sigma_ * sigma_)) / (M_PI_2 * sigma_ * sigma_);
        }
    }
    image.applyConv(kernel);
}

