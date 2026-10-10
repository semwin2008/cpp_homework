#pragma once

#include <unordered_map>
#include <functional>
#include "utils/filter/crop/crop.h"


// Factory
const std::unordered_map<const std::string, 
std::function<std::unique_ptr<Filter>(const FilterArgs&)>> NAME_FILTER_MATCH = {
    {"crop", cropFactory}
};
