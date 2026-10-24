#include "writer.h"
#include "reader.h"
#include <fstream>
#include <vector>
#include <stdexcept>
#include <cstdint>
#include "../exceptions/exceptions.h"

void BMP::write(const std::string& path, const Image& image) {
    std::ofstream fout(path, std::ios::binary);
    if (!fout) {
        throw FileNotFoundException("Tried to write to file: " + path);
    }
    size_t width = image.GetWidth();
    size_t height = image.GetHeight();
    if (width == 0 || height == 0) {
        throw std::runtime_error("Cannot write empty image to BMP");
    }
    size_t rowSizeWithoutPadding = width * 3;
    size_t rowSize = ((rowSizeWithoutPadding + 3) / 4) * 4;
    
    const size_t headers_size = sizeof(BMP::BitmapFileHeader) + sizeof(BMP::BitmapInfoHeader);
    const size_t pixel_data_size = rowSize * height;
    const size_t file_size = headers_size + pixel_data_size;

    BMP::BitmapFileHeader file_header{};
    file_header.bfType = BFTYPE;
    file_header.bfSize = static_cast<uint32_t>(file_size);
    file_header.bfReserved1 = 0;
    file_header.bfReserved2 = 0;
    file_header.bfOffBits = static_cast<uint32_t>(headers_size);

    BMP::BitmapInfoHeader info_header{};
    info_header.biSize = static_cast<uint32_t>(sizeof(BMP::BitmapInfoHeader));
    info_header.biWidth = static_cast<int32_t>(width);
    info_header.biHeight = static_cast<int32_t>(height);
    info_header.biPlanes = 1;
    info_header.biBitCount = BIBITCOUNT;
    info_header.biCompression = 0; // BI_RGB
    info_header.biSizeImage = static_cast<uint32_t>(pixel_data_size);
    info_header.biXPelsPerMeter = 0;
    info_header.biYPelsPerMeter = 0;
    info_header.biClrUsed = 0;
    info_header.biClrImportant = 0;

    fout.write(reinterpret_cast<const char*>(&file_header), sizeof(file_header));
    fout.write(reinterpret_cast<const char*>(&info_header), sizeof(info_header));
    if (!fout) {
        throw UnableToWriteFileException("tried writing output file headers");
    }
    std::vector<uint8_t> rowBuffer(rowSize, 0); 
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            size_t sourceRowIndex = height - 1 - i;
            Pixel pixel = image.At(sourceRowIndex, j);
            size_t byteIndex = j * 3;
            rowBuffer[byteIndex]     = static_cast<uint8_t>(pixel.b * PIXEL_MAX_VALUE);
            rowBuffer[byteIndex + 1] = static_cast<uint8_t>(pixel.g * PIXEL_MAX_VALUE);
            rowBuffer[byteIndex + 2] = static_cast<uint8_t>(pixel.r * PIXEL_MAX_VALUE);
        }
        
        fout.write(reinterpret_cast<const char*>(rowBuffer.data()), rowSize);
        if (!fout) {
            throw UnableToWriteFileException("tried to write output pixels to file");
        }
    }
}