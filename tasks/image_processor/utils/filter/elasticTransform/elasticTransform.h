#pragma once

#include "../filter.h"
#include "../../args/args.h"
#include "../gaussianBlur/gaussianBlur.h"
#include <string>
#include <random>


class ElasticTransform : public Filter {
public:
    ElasticTransform(const FilterArgs& args);
    void apply(Image& image) override;
private:
    float alpha_;
    GaussianBlur blur_;
    std::string interpolation_mode_ = "nearest";
    std::mt19937 gen_;
};
