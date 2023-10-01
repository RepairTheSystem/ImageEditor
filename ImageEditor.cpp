
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Типы данных BMP-файла
#pragma pack(push, 1)
struct BMPHeader {
    uint16_t signature;
    uint32_t img_size;
    uint32_t reserved;
    uint32_t data_offset;
    uint32_t header_size;
    int32_t width;
    int32_t height;
    uint16_t color_planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t image_size;
    int32_t x_pixels_per_meter;
    int32_t y_pixels_per_meter;
    uint32_t colors_used;
    uint32_t important_colors;
};
#pragma pack(pop)

struct pixel_struct{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

// Функция для поворота изображения на 90 градусов по часовой стрелке
void rotateImage(std::vector<pixel_struct>& pix, int width, int height) {
    vector<pixel_struct> new_pix(pix.size());

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int new_x = y;
            int new_y = width - x - 1;
            
            int original_index = y * width + x;
            int new_index = new_y * height + new_x;
            
            new_pix[new_index] = pix[original_index];
        }
    }

    pix = new_pix;
}

int main() {
    ifstream img("C://CODE//C++//ImageEditor//Rainier.bmp", ios::binary);
    ofstream new_img("C://CODE//C++//ImageEditor//new_img.bmp", ios::binary);

    if (!img.is_open()) {
        cout << "Не удалось открыть файл!" << endl;
        return 0;
    }

    BMPHeader header;

    img.read(reinterpret_cast<char*>(&header), sizeof(header));

    // Вычисление размера изображения
    int width = header.width;
    int height = header.height;

    // Выделение памяти для хранения пикселей изображения
    vector<pixel_struct> pix(width * height);

    // Чтение пикселей изображения
    img.read(reinterpret_cast<char*>(pix.data()), pix.size() * 3);
    // Запись заголовков BMP в выходной файл
    BMPHeader new_header = header;
    new_header.width = height;
    new_header.height = width;
    new_img.write(reinterpret_cast<const char*>(&new_header), sizeof(new_header));

    // Создание выходного файла

    // Поворот изображения
    rotateImage(pix, width, height);

    // Запись пикселей изображения в выходной файл
    new_img.write(reinterpret_cast<const char *>(pix.data()), pix.size() * 3);

    cout << "Изображение успешно повернуто и сохранено в файле 'output.bmp'." << endl;

return 0;
}