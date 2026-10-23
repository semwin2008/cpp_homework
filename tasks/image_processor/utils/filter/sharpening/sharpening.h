#pragma once

#include "utils/filter/filter.h"
#include "utils/args/args.h"


class Sharpening : Filter {
public:
    Sharpening(const FilterArgs& args) {}
    void apply(Image& image) override;
private:
};
