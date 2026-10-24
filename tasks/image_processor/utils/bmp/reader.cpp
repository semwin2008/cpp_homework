#include "reader.h"
#include <fstream>
#include "../exceptions/exceptions.h"
#include <vector>



Image BMP::read(const std::string& file) {
    // opening the file
    std::ifstream fin(file, std::ios::binary);
    if (!fin) {
        throw FileNotFoundException("Tried to read input file");
    }
    BMP::BitmapFileHeader file_header{};
    BMP::BitmapInfoHeader info_header{};
    fin.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    if (!fin) {
        throw BadFileFormatException("tried to read file header");
    }
    fin.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));
    if (!fin) {
        throw BadFileFormatException("tried to read info header");
    }
    // format validation
    if (file_header.bfType != 0x4D42) { // 'B' 'M' в little-endian
        throw BadFileFormatException("input file has wrong bfType");
    }
    if (info_header.biBitCount != 24) {
        throw BadFileFormatException("input file has wrong biBitCount");
    }
    if (info_header.biCompression != 0) {
        throw BadFileFormatException("input file is compressed");
    }
    // reading grid parameters
    bool topDown = info_header.biHeight < 0;
    size_t outWidth = info_header.biWidth;
    size_t outHeight = topDown ? -info_header.biHeight : info_header.biHeight;
    if (outWidth <= 0 || outHeight <= 0) {
        throw BadFileFormatException("input file contains empty image");
    }
    // reading pixels
    size_t pixelCount = outWidth * outHeight;
    std::vector<BMP::Pixel32> pixels(pixelCount);
    fin.seekg(file_header.bfOffBits, std::ios::beg);
    fin.read(reinterpret_cast<char*>(pixels.data()), pixelCount * sizeof(Pixel32));
    if (!fin) {
        throw BadFileFormatException("tried to read the pixels");
    }
    // Creating an Image
    Image image(outHeight, outWidth);
    for (size_t i = 0, index = 0; i < outHeight; ++i) {
        for (size_t j = 0; j < outWidth; ++j, ++index) {
            size_t i_index = topDown ? outHeight - 1 - i : i;
            image.At(i_index, j) = Pixel(
                pixels[index].r,
                pixels[index].g,
                pixels[index].b
            );
        }
    }
    return image;
}

