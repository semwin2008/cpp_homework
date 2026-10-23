#pragma once

#include "utils/filter/filter.h"
#include "utils/args/args.h"


class Negative : Filter {
public:
    Negative(const FilterArgs& args) {}
    void apply(Image& image) override;
private:
};
