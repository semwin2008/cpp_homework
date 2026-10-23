#pragma once

#include "utils/filter/filter.h"
#include "utils/args/args.h"
#include <string>


class ElasticTransform : Filter {
public:
    ElasticTransform(const FilterArgs& args);
    void apply(Image& image) override;
private:
    float alpha_;
    float sigma_;
    std::string interpolation_mode_ = "nearest";
    int seed_ = -1;
};
