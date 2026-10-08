#pragma once

#include "filter/filter.h"
#include <vector>


class Pipeline : Filter{
public:
private:
    std::vector<Filter> filters;
};
