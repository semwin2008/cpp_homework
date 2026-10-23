#pragma once

#include <unordered_map>
#include <functional>
#include "utils/filter/crop/crop.h"


template<class Filt>
std::unique_ptr<Filter> Factory(const FilterArgs& args) {
    return std::make_unique<Filter>(Filt(args));
}

const std::unordered_map<const std::string, 
std::function<std::unique_ptr<Filter>(const FilterArgs&)>> NAME_FILTER_MATCH = {
    {"crop", Factory<Crop>}
};
