#include "image.h"
#include <iostream>
#include "../exceptions/exceptions.h"
#include <algorithm>
#include <complex>
#include <cmath>
#include <vector>


Pixel Pixel::operator+(const Pixel& rhs) const {
    return Pixel{
        r + rhs.r,
        g + rhs.g,
        b + rhs.b
    };
}

void Pixel::operator+=(const Pixel& rhs) {
    r += rhs.r;
    g += rhs.g;
    b += rhs.b;
}

Pixel Pixel::operator-(const Pixel& rhs) const {
    return Pixel{
        r - rhs.r,
        g - rhs.g,
        b - rhs.b
    };
}

Pixel Pixel::operator*(const Pixel& rhs) const {
    return Pixel{
        r * rhs.r,
        g * rhs.g,
        b * rhs.b
    };
}

Pixel& Image::At(int i, int j) {
    if (i < 0) i = 0;
    if (i >= GetHeight()) i = GetHeight() - 1;
    if (j < 0) j = 0;
    if (j >= GetWidth()) j = GetWidth() - 1;
    return matrix_[i][j];
}

void Pixel::Clamp(float a, float bb) {
    r = std::min(bb, std::max(a, r));
    g = std::min(bb, std::max(a, g));
    b = std::min(bb, std::max(a, b));
}


// Структура для комплексных чисел (если нет std::complex)
using Complex = std::complex<double>;

// Быстрое преобразование Фурье (Cooley-Tukey algorithm)
void FFT(std::vector<Complex>& data, bool inverse = false) {
    int n = data.size();
    if (n <= 1) return;
    
    // Битовая реверсия
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) {
            j ^= bit;
        }
        j ^= bit;
        if (i < j) {
            std::swap(data[i], data[j]);
        }
    }
    
    // Бабочка
    for (int len = 2; len <= n; len <<= 1) {
        double angle = -2 * M_PI / len * (inverse ? -1 : 1);
        Complex wlen(std::cos(angle), std::sin(angle));
        
        for (int i = 0; i < n; i += len) {
            Complex w(1, 0);
            for (int j = 0; j < len / 2; ++j) {
                Complex u = data[i + j];
                Complex v = data[i + j + len / 2] * w;
                data[i + j] = u + v;
                data[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    
    if (inverse) {
        for (auto& x : data) {
            x /= n;
        }
    }
}

// 2D FFT для одного канала
void FFT2D(std::vector<std::vector<Complex>>& data, bool inverse = false) {
    int rows = data.size();
    if (rows == 0) return;
    int cols = data[0].size();
    
    // FFT по строкам
    for (int i = 0; i < rows; ++i) {
        FFT(data[i], inverse);
    }
    
    // FFT по столбцам
    std::vector<Complex> col(rows);
    for (int j = 0; j < cols; ++j) {
        for (int i = 0; i < rows; ++i) {
            col[i] = data[i][j];
        }
        FFT(col, inverse);
        for (int i = 0; i < rows; ++i) {
            data[i][j] = col[i];
        }
    }
}

// Следующая степень двойки
int NextPowerOfTwo(int n) {
    int power = 1;
    while (power < n) {
        power <<= 1;
    }
    return power;
}

// Свертка одного канала через FFT
std::vector<std::vector<float>> ConvolveChannelFFT(
    const std::vector<std::vector<float>>& image,
    const std::vector<std::vector<float>>& kernel) 
{
    int imgHeight = image.size();
    int imgWidth = image[0].size();
    int kernHeight = kernel.size();
    int kernWidth = kernel[0].size();
    
    // Размер для FFT (чтобы избежать циклической свертки)
    int fftHeight = NextPowerOfTwo(imgHeight + kernHeight - 1);
    int fftWidth = NextPowerOfTwo(imgWidth + kernWidth - 1);
    
    // Создаем padded массивы
    std::vector<std::vector<Complex>> imgFFT(fftHeight, std::vector<Complex>(fftWidth, 0));
    std::vector<std::vector<Complex>> kernFFT(fftHeight, std::vector<Complex>(fftWidth, 0));
    
    // Копируем изображение
    for (int i = 0; i < imgHeight; ++i) {
        for (int j = 0; j < imgWidth; ++j) {
            imgFFT[i][j] = Complex(image[i][j], 0);
        }
    }
    
    // Копируем ядро (центрируем его)
    int kernOffsetY = kernHeight / 2;
    int kernOffsetX = kernWidth / 2;
    for (int i = 0; i < kernHeight; ++i) {
        for (int j = 0; j < kernWidth; ++j) {
            int pos_i = i;
            int pos_j = j;
            kernFFT[pos_i][pos_j] = Complex(kernel[i][j], 0);
        }
    }
    
    // Применяем 2D FFT
    FFT2D(imgFFT, false);
    FFT2D(kernFFT, false);
    
    // Поэлементное умножение в частотной области
    for (int i = 0; i < fftHeight; ++i) {
        for (int j = 0; j < fftWidth; ++j) {
            imgFFT[i][j] *= kernFFT[i][j];
        }
    }
    
    // Обратное FFT
    FFT2D(imgFFT, true);
    
    // Извлекаем результат нужного размера
    std::vector<std::vector<float>> result(imgHeight, std::vector<float>(imgWidth, 0));
    for (int i = 0; i < imgHeight; ++i) {
        for (int j = 0; j < imgWidth; ++j) {
            result[i][j] = imgFFT[i][j].real();
        }
    }
    
    return result;
}

void Image::applyConv(const std::vector<std::vector<float>>& kernel) {
    if (kernel.empty()) {
        throw EmptyKernelException("kernel cannot be empty");
    }
    
    int height = GetHeight();
    int width = GetWidth();
    
    // Извлекаем каналы
    std::vector<std::vector<float>> red(height, std::vector<float>(width));
    std::vector<std::vector<float>> green(height, std::vector<float>(width));
    std::vector<std::vector<float>> blue(height, std::vector<float>(width));
    
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            auto [r, g, b] = matrix_[i][j];
            red[i][j] = r;
            green[i][j] = g;
            blue[i][j] = b;
        }
    }
    
    // Применяем свертку к каждому каналу
    auto redResult = ConvolveChannelFFT(red, kernel);
    auto greenResult = ConvolveChannelFFT(green, kernel);
    auto blueResult = ConvolveChannelFFT(blue, kernel);
    
    // Записываем результат обратно
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            matrix_[i][j] = Pixel{
                static_cast<float>(redResult[i][j]),
                static_cast<float>(greenResult[i][j]),
                static_cast<float>(blueResult[i][j])
            };
        }
    }
}


void Image::NormalizeValues() {
    for (size_t i = 0; i < GetHeight(); ++i) {
        for (size_t j = 0; j < GetWidth(); ++j) {
            At(i, j).Clamp(0.0, 1.0);
        }
    }
}
