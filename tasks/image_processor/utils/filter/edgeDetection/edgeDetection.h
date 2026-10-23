#pragma once

#include "utils/filter/filter.h"
#include "utils/args/args.h"


class EdgeDetection : Filter {
public:
    EdgeDetection(const FilterArgs& args);
    void apply(Image& image) override;
private:
    float threshold_;
};
