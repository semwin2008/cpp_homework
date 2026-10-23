#include "edgeDetection.h"
#include "../../exceptions/exceptions.h"
#include "../grayscale/grayscale.h"


EdgeDetection::EdgeDetection(const FilterArgs& args) {
    if (args.size() != 1) {
        throw BadFilterArgument();
    }
    threshold_ = std::stof(args[0]);
}

void EdgeDetection::apply(Image& image) {
    Grayscale grayscale({});
    grayscale.apply(image);
    std::vector<std::vector<float>> kernel = {
        { 0.0, -1.0,  0.0},
        {-1.0,  4.0, -1.0},
        { 0.0, -1.0,  0.0}
    };
    image.applyConv(kernel);
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            image.At(i, j).r = image.At(i, j).r > threshold_ ? 1.0f : 0.0f;
            image.At(i, j).g = image.At(i, j).g > threshold_ ? 1.0f : 0.0f;
            image.At(i, j).b = image.At(i, j).b > threshold_ ? 1.0f : 0.0f;
        }
    }
}
