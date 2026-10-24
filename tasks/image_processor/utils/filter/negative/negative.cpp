#include "negative.h"
#include "../../exceptions/exceptions.h"


Negative::Negative(const FilterArgs& args) {
    if (args.size() != 0) {
        throw BadFilterArgumentException("negative takes no args");
    }
}

void Negative::apply(Image& image) {
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            image.At(i, j) = Pixel(1.0f) - image.At(i, j);
        }
    }
}
