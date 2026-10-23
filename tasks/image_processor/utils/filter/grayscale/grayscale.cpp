#include "grayscale.h"
#include "../../exceptions/exceptions.h"


Grayscale::Grayscale(const FilterArgs& args) {
    if (args.size() != 0) {
        throw BadFilterArgument();
    }
}

void Grayscale::apply(Image& image) {
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            auto [r, g, b] = image.At(i, j);
            float value = 0.299 * r + 0.587 * g + 0.114 * b;
            image.At(i, j) = value;
        }
    }
}
