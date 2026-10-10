#include "utils/filter/crop/crop.h"


std::unique_ptr<Filter> cropFactory(const FilterArgs& args) {
    if (args.args.size() != 2) {
        throw "filter crop takes exactly 2 arguments";
    }
    return std::make_unique<Filter>(Crop(args));
}

Crop::Crop(const FilterArgs& args) {
    
}

Image Crop::apply(const Image& image) {
    
}
