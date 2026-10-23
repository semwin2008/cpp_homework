#include "crop.h"
#include "../../exceptions/exceptions.h"


Crop::Crop(const FilterArgs& args) {
    if (args.size() != 2) {
        throw BadFilterArgument();
    }
    height_ = std::stoull(args[1]);
    width_ = std::stoull(args[0]);
    if (height_ == 0 || width_ == 0) {
        throw BadFilterArgument();
    }
}

void Crop::apply(Image& image) {
    size_t result_height = std::min(image.GetHeight(), height_);
    size_t result_width = std::min(image.GetWidth(), width_);
    Image result(result_height, result_width);
    for (size_t i = 0; i < result_height; ++i) {
        for (size_t j = 0; j < result_width; ++j) {
            result.At(i, j) = image.At(i, j);
        }
    }
    image = std::move(result);
}
