#pragma once

#include "../filter.h"
#include "../../args/args.h"


class Negative : public Filter {
public:
    Negative(const FilterArgs& args) {}
    void apply(Image& image) override;
private:
};
