#pragma once

#include "utils/filter/filter.h"
#include "utils/args/filterArgs.h"
#include <memory>


std::unique_ptr<Filter> grayscaleFactory(const FilterArgs& args);

class Grayscale : Filter {
public:
    Grayscale(const FilterArgs& args);
    void apply(Image& image) override;
private:
};
