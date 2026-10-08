#pragma once

#include "image/image.h"
#include <string>


namespace BMP{

    // reads the image from bmp file
    Image read(const std::string& path);

}
