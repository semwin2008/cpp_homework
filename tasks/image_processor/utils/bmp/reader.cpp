#include "reader.h"
#include <fstream>
#include "../exceptions/exceptions.h"
#include <vector>
#include <cstdint>
#include <iostream>
#include <cmath>


Image BMP::read(const std::string& file) {
    std::ifstream fin(file, std::ios::binary);
    if (!fin) {
        throw FileNotFoundException("Tried to read input file");
    }

    BMP::BitmapFileHeader file_header{};
    BMP::BitmapInfoHeader info_header{};
    
    fin.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    if (!fin) throw BadFileFormatException("tried to read file header");

    fin.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));
    if (!fin) throw BadFileFormatException("tried to read info header");

    if (file_header.bfType != BFTYPE) {
        throw BadFileFormatException("input file has wrong bfType");
    }
    if (info_header.biBitCount != BIBITCOUNT) {
        throw BadFileFormatException("input file has wrong biBitCount, expected 24, got " + std::to_string(info_header.biBitCount));
    }
    if (info_header.biCompression != 0) {
        throw BadFileFormatException("input file is compressed");
    }

    bool topDown = info_header.biHeight < 0;
    size_t outWidth = static_cast<size_t>(std::abs(info_header.biWidth));
    size_t outHeight = static_cast<size_t>(std::abs(info_header.biHeight));
    
    if (outWidth == 0 || outHeight == 0) {
        throw BadFileFormatException("input file contains empty image");
    }

    size_t rowSizeWithoutPadding = outWidth * 3;
    size_t rowSize = ((rowSizeWithoutPadding + 3) / 4) * 4;
    fin.seekg(file_header.bfOffBits, std::ios::beg);

    fin.seekg(0, std::ios::end);
    size_t fileSize = fin.tellg();
    fin.seekg(file_header.bfOffBits, std::ios::beg);
    Image image(outHeight, outWidth);
    std::vector<uint8_t> rowBuffer(rowSize);

    for (size_t i = 0; i < outHeight; ++i) {
        fin.read(reinterpret_cast<char*>(rowBuffer.data()), rowSize);
        if (!fin) {
            throw BadFileFormatException("tried to read the pixels");
        }

        for (size_t j = 0; j < outWidth; ++j) {
            size_t byteIndex = j * 3;
            uint8_t b = rowBuffer[byteIndex];
            uint8_t g = rowBuffer[byteIndex + 1];
            uint8_t r = rowBuffer[byteIndex + 2];

            size_t i_index = topDown ? i : (outHeight - 1 - i);
            image.At(i_index, j) = Pixel(r, g, b);
        }
    }
    return image;
}
