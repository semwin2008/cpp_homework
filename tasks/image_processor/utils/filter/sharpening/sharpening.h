#pragma once

#include "../filter.h"
#include "../../args/args.h"


class Sharpening : public Filter {
public:
    Sharpening(const FilterArgs& args) {}
    void apply(Image& image) override;
private:
};
