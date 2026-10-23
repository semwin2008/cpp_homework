#pragma once

#include "utils/filter/filter.h"
#include "utils/args/args.h"


class Grayscale : Filter {
public:
    Grayscale(const FilterArgs& args);
    void apply(Image& image) override;
private:
};
