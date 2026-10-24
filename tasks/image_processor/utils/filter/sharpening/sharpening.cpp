#include "sharpening.h"
#include "../../exceptions/exceptions.h"


Sharpening::Sharpening(const FilterArgs& args) {
    if (args.size() != 0) {
        throw BadFilterArgumentException("sharpening takes no args");
    }
}

void Sharpening::apply(Image& image) {
    std::vector<std::vector<float>> kernel = {
        { 0.0, -1.0,  0.0},
        {-1.0,  5.0, -1.0},
        { 0.0, -1.0,  0.0}
    };
    image.applyConv(kernel);
}
