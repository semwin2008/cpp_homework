#pragma once

#include "../filter.h"
#include "../../args/args.h"


class GaussianBlur : public Filter {
public:
    GaussianBlur() = default;
    GaussianBlur(const FilterArgs& args);
    void apply(Image& image) override;
private:
    float sigma_ = 0;
};
