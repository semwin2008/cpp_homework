#include "utils/bmp/reader.h"
#include <fstream>
#include "utils/exceptions/exceptions.h"
#include <vector>



Image BMP::read(const std::string& file) {
    // opening the file
    std::ifstream fin(file, std::ios::binary);
    if (!fin) {
        throw FileNotFoundException();
    }
    BMP::BitmapFileHeader file_header{};
    BMP::BitmapInfoHeader info_header{};
    fin.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    if (!fin) {
        throw BadFileFormat();
    }
    fin.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));
    if (!fin) {
        throw BadFileFormat();
    }
    // format validation
    if (file_header.bfType != 0x4D42) { // 'B' 'M' в little-endian
        throw BadFileFormat();
    }
    if (info_header.biBitCount != 32) {
        throw BadFileFormat();
    }
    if (info_header.biCompression != 0) {
        throw BadFileFormat();
    }
    // reading grid parameters
    bool topDown = info_header.biHeight < 0;
    size_t outWidth = info_header.biWidth;
    size_t outHeight = topDown ? -info_header.biHeight : info_header.biHeight;
    if (outWidth <= 0 || outHeight <= 0) {
        throw BadFileFormat();
    }
    // reading pixels
    size_t pixelCount = outWidth * outHeight;
    std::vector<BMP::Pixel32> pixels(pixelCount);
    fin.seekg(file_header.bfOffBits, std::ios::beg);
    fin.read(reinterpret_cast<char*>(pixels.data()), pixelCount * sizeof(Pixel32));
    if (!fin) {
        throw BadFileFormat();
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

