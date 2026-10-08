#pragma once

#include "image/image.h"
#include <string>


namespace BMP{

    // writes the image to bmp file
    void write(const std::string& path, const Image& image);

}
