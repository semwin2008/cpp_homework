#include "utils/filter/edgeDetection/edgeDetection.h"
#include "utils/exceptions/exceptions.h"
#include "utils/filter/grayscale/grayscale.h"


EdgeDetection::EdgeDetection(const FilterArgs& args) {
    if (args.size() != 1) {
        throw BadFilterArgument();
    }
    threshold_ = std::stof(args[0]);
}

void EdgeDetection::apply(Image& image) {
    Grayscale grayscale({});
    grayscale.apply(image);

}
