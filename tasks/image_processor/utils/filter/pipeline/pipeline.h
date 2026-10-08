#pragma once

#include "filter/filter.h"
#include "utils/args/filterArgs.h"
#include <vector>


class Pipeline : Filter{
public:
    Pipeline(const FilterArgs& args);
    
    Image apply(const Image& image);
private:
    std::vector<Filter> filters;
};
