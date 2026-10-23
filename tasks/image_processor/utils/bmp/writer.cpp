#include "utils/bmp/writer.h"
#include "utils/bmp/reader.h"
#include <fstream>
#include <vector>
#include <stdexcept>
#include "utils/exceptions/exceptions.h"


void BMP::write(const std::string& path, const Image& image) {
    std::ofstream fout(path, std::ios::binary);
    if (!fout) {
        throw FileNotFoundException();
    }

    // ⚠️ Замените GetHeight() / GetWidth() на актуальные методы вашего класса Image
    // (например, Height() / Width() или прямое обращение к полям).
    size_t width = image.GetWidth();
    size_t height = image.GetHeight();

    if (width == 0 || height == 0) {
        throw std::runtime_error("Cannot write empty image to BMP");
    }

    // 1. Подготовка заголовков
    const size_t headers_size = sizeof(BMP::BitmapFileHeader) + sizeof(BMP::BitmapInfoHeader);
    const size_t pixel_data_size = width * height * sizeof(BMP::Pixel32);
    const size_t file_size = headers_size + pixel_data_size;

    BMP::BitmapFileHeader file_header{};
    file_header.bfType = 0x4D42; // "BM"
    file_header.bfSize = static_cast<uint32_t>(file_size);
    file_header.bfReserved1 = 0;
    file_header.bfReserved2 = 0;
    file_header.bfOffBits = static_cast<uint32_t>(headers_size);

    BMP::BitmapInfoHeader info_header{};
    info_header.biSize = static_cast<uint32_t>(sizeof(BMP::BitmapInfoHeader));
    info_header.biWidth = static_cast<int32_t>(width);
    info_header.biHeight = static_cast<int32_t>(height); // Положительный -> bottom-up (стандарт)
    info_header.biPlanes = 1;
    info_header.biBitCount = 32;
    info_header.biCompression = 0; // BI_RGB
    info_header.biSizeImage = static_cast<uint32_t>(pixel_data_size);
    info_header.biXPelsPerMeter = 0;
    info_header.biYPelsPerMeter = 0;
    info_header.biClrUsed = 0;
    info_header.biClrImportant = 0;

    // 2. Запись заголовков
    fout.write(reinterpret_cast<const char*>(&file_header), sizeof(file_header));
    fout.write(reinterpret_cast<const char*>(&info_header), sizeof(info_header));

    if (!fout) {
        throw UnableToWriteFile();
    }

    // 3. Запись пикселей
    // В BMP без сжатия строки хранятся снизу вверх (bottom-up).
    // Строка 0 в файле — это нижняя граница изображения.
    std::vector<BMP::Pixel32> row_buffer(width);
    for (size_t i = 0; i < height; ++i) {        
        for (size_t j = 0; j < width; ++j) {
            size_t i_index = height - 1 - i;
            const auto& pixel = image.At(i_index, j);
            // Формат BMP: B, G, R, A
            row_buffer[j] = {
                static_cast<uint8_t>(pixel.b),
                static_cast<uint8_t>(pixel.g),
                static_cast<uint8_t>(pixel.r),
                255
            };
        }
        fout.write(reinterpret_cast<const char*>(row_buffer.data()), row_buffer.size() * sizeof(BMP::Pixel32));
        if (!fout) {
            throw UnableToWriteFile();
        }
    }
}
