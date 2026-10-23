#pragma once

#include "utils/filter/filter.h"
#include "utils/args/filterArgs.h"
#include <memory>


class Crop : Filter {
public:
    Crop(const FilterArgs& args);
    void apply(Image& image) override;
private:
    size_t height_;
    size_t width_;
};
