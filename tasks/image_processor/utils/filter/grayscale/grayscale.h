#pragma once

#include "../filter.h"
#include "../../args/args.h"


class Grayscale : public Filter {
public:
    Grayscale(const FilterArgs& args);
    void apply(Image& image) override;
private:
};
