#include "negative.h"


void Negative::apply(Image& image) {
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            image.At(i, j) = Pixel(1.0f) - image.At(i, j);
        }
    }
}
