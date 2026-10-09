#pragma once

#include "filter/filter.h"
#include "utils/args/filterArgs.h"
#include <vector>
#include <memory>


class Pipeline : Filter{
public:
    Pipeline(const FilterArgs& args) = delete;
    Pipeline(const std::vector<FilterArgs>& args);
    
    Image apply(const Image& image);
private:
    std::vector<std::unique_ptr<Filter>> filters;
};
