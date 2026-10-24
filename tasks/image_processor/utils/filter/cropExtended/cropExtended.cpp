#include "cropExtended.h"
#include "../../exceptions/exceptions.h"


CropExtended::CropExtended(const FilterArgs& args) {
    if (args.size() != 2 && args.size() != 4) {
        throw BadFilterArgumentException("Crop Extended takes 2 or 4 args");
    }
    height_ = std::stoull(args[0]);
    width_ = std::stoull(args[1]);
    if (args.size() == 4) {
        start_x_ = std::stoull(args[2]);
        start_y_ = std::stoull(args[3]);
    }
}

void CropExtended::apply(Image& image) {
    size_t result_height = std::min(image.GetHeight(), height_);
    size_t result_width = std::min(image.GetWidth(), width_);
    Image result(result_height, result_width);
    size_t start_x = std::min(start_x_, image.GetHeight() - result_height);
    size_t start_y = std::min(start_y_, image.GetWidth() - result_width);
    for (size_t i = 0; i < result_height; ++i) {
        for (size_t j = 0; j < result_width; ++j) {
            result.At(i, j) = image.At(i + start_x, j + start_y);
        }
    }
    image = std::move(result);
}

