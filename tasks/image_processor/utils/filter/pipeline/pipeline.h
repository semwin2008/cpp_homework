#pragma once

#include "../filter.h"
#include "../../args/args.h"
#include <vector>
#include <memory>


class Pipeline : public Filter{
public:
    Pipeline(const FilterArgs& args) = delete;
    Pipeline(const std::vector<std::pair<std::string, FilterArgs>>& args);
    
    void apply(Image& image);
private:
    std::vector<std::unique_ptr<Filter>> filters_;
};
