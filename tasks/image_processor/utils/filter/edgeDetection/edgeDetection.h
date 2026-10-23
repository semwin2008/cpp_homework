#pragma once

#include "../filter.h"
#include "../../args/args.h"


class EdgeDetection : public Filter {
public:
    EdgeDetection(const FilterArgs& args);
    void apply(Image& image) override;
private:
    float threshold_;
};
