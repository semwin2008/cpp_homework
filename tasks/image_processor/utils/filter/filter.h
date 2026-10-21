#pragma once

#include "image/image.h"


class Filter{
public:
    virtual void apply(const Image& image, Image& result) = 0;
};
