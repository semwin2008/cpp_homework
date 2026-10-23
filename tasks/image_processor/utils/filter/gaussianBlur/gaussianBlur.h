#pragma once

#include "utils/filter/filter.h"
#include "utils/args/args.h"


class GaussianBlur : Filter {
public:
    GaussianBlur(const FilterArgs& args);
    void apply(Image& image) override;
private:
    float sigma_;
};
