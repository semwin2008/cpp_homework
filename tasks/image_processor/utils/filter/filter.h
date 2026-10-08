#pragma once

#include "image/image.h"


class Filter{
public:
    virtual Image apply(const Image& image) = 0;
};
