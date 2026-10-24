#pragma once

#include "../../args/args.h"
#include "../filter.h"


class CropExtended : public Filter {
public:
    CropExtended(const FilterArgs& args);
    void apply(Image& image);

private:
    size_t height_;
    size_t width_;
    size_t start_x_ = 0;
    size_t start_y_ = 0;
};
