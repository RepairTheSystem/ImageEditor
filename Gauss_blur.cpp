// Gauss blur function
#include <cmath>
#include "Gauss_blur.h"

// calculate the Gaussian kernel
std::vector<double>gauss_kernel(int radius){
    std::vector<double> kernel(2 * radius + 1);
    double sigma = static_cast<double>(radius) / 3.0;
    double sum = 0.0;

    for (int x = -radius; x <= radius; ++x) {
        double value = exp(-0.5 * (x * x) / (sigma * sigma));
        kernel[x + radius] = value;
        sum += value;
    }
    
    for (int i = 0; i < 2 * radius + 1; ++i) {
        kernel[i] /= sum;
    }
    return kernel;
}

void gauss(std::vector<pixel_struct>& pix, int width, int height, int radius) {
    std::vector<pixel_struct> blur_pix(width * height);
    std::vector<double> kernel = gauss_kernel(radius);
    // apply a blur
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double r = 0.0, g = 0.0, b = 0.0;
            int index = y * width + x;
            for (int i = -radius; i <= radius; i++) {
                int neighbor_X = x + i;
                if (neighbor_X >= 0 and neighbor_X < width) {
                    int neighbor_index = y * width + neighbor_X;
                    double weight = kernel[i + radius];

                    r += pix[neighbor_index].red * weight;
                    g += pix[neighbor_index].green * weight;
                    b += pix[neighbor_index].blue * weight;
                }
            }
            blur_pix[index].red = static_cast<unsigned char>(r);
            blur_pix[index].green = static_cast<unsigned char>(g);
            blur_pix[index].blue = static_cast<unsigned char>(b);
        }
    }
    // обновляем массив пикселей
    pix = blur_pix;
}
