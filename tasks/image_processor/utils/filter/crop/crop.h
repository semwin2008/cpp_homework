#pragma once

#include "../../filter/filter.h"
#include "../../args/args.h"


class Crop : public Filter {
public:
    Crop(const FilterArgs& args);
    void apply(Image& image) override;
private:
    size_t height_;
    size_t width_;
};
