#pragma once

#include "../image/image.h"


class Filter{
public:
    virtual void apply(Image& image) = 0;
};
