#include "rotate.h"
void rotate_right(std::vector<pixel_struct>& pix, BMPHeader &header) {
    std::vector<pixel_struct> new_pix(pix.size());
    int width = header.width;
    int height = header.height;

    // симметрично отражаем каждый пиксель
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int new_x = y;
            int new_y = width - x - 1;
            
            int original_index = y * width + x;
            int new_index = new_y * height + new_x;
            
            new_pix[new_index] = pix[original_index];
        }
    }
    // меняем параметры заголвка для нового файла
    header.width = height;
    header.height = width;

    // обновляем массив пикселей
    pix = new_pix;
}
 
// функция для поворота изображения на 90 градусов против часовой стрелки
void rotate_left(std::vector<pixel_struct>& pix, BMPHeader &header) {
    std::vector<pixel_struct> new_pix(pix.size());
    int width = header.width;
    int height = header.height;

    // симметрично отражаем каждый пиксель
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int new_x = height - y - 1;
            int new_y = x;

            int original_index = y * width + x;
            int new_index = new_y * height + new_x;

            new_pix[new_index] = pix[original_index];
        }
    }
    // меняем параметры заголвка для нового файла
    header.width = height;
    header.height = width;

    // обновляем массив пикселей
    pix = new_pix;
}
