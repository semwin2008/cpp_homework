#include "sharpening.h"


void Sharpening::apply(Image& image) {
    std::vector<std::vector<float>> kernel = {
        { 0.0, -1.0,  0.0},
        {-1.0,  5.0, -1.0},
        { 0.0, -1.0,  0.0}
    };
    image.applyConv(kernel);
}
