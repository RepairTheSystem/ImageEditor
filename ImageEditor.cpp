#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

// стуруктура хранения заголовка
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

// структура хранения пикселей
struct pixel_struct{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

// функция размытия по Гауссу
void gauss(vector<pixel_struct>& pix, int width, int height, int radius) {
    vector<pixel_struct> blur_pix(width * height);

    // вычисляем Гауссово ядро
    vector<double> kernel(2 * radius + 1);
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

    // применяем размытие
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double r = 0.0, g = 0.0, b = 0.0;
            int index = y * width + x;

            for (int i = -radius; i <= radius; ++i) {
                int neighborX = x + i;
                if (neighborX >= 0 && neighborX < width) {
                    int neighborIndex = y * width + neighborX;
                    double weight = kernel[i + radius];

                    r += pix[neighborIndex].red * weight;
                    g += pix[neighborIndex].green * weight;
                    b += pix[neighborIndex].blue * weight;
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


// функция для поворота изображения на 90 градусов против часовой стрелки
void rotate_left(vector<pixel_struct>& pix, BMPHeader &header) {
    vector<pixel_struct> new_pix(pix.size());
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

// функция для поворота изображения на 90 градусов по часовой стрелке
void rotate_right(vector<pixel_struct>& pix, BMPHeader &header) {
    vector<pixel_struct> new_pix(pix.size());
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

int main() {
    // инициализация файла
    cout << "Введит название исходного файла (без .bmp): ";
    string file_name;

    cin >> file_name;
    file_name += ".bmp";

    ifstream img(file_name, ios::binary);
    ofstream new_img("new_img.bmp", ios::binary | ios::trunc);

    // проверка на корректность ввода 
    if (!img.is_open()) {
        cout << "Не удалось открыть файл!" << endl;
        return 0;
    }

    // работаем с заголовком
    BMPHeader header;

    img.read(reinterpret_cast<char*>(&header), sizeof(header));

    int width = header.width;
    int height = header.height;

    // вектор хранения пикселей
    vector<pixel_struct> pix(width * height);

    img.read(reinterpret_cast<char*>(pix.data()), pix.size() * 3);

    // логика интерфейса пользователя
    char command1;
    cout << "Введите команду для поворота " << endl;
    cout << "1 - поворот на 90 градусов вправо, 2 - поворот на 90 градусов влево, 0 - без поворота ";
    cin >> command1;

    if (command1 == '1')
        rotate_right(pix, header);
    else if (command1 == '2')
        rotate_right(pix, header);
    
    int radius;
    cout << "Введите глубину размытия по Гауссу " << endl;
    cout << "(если размывать не нужно введите 0, иначе целое число) ";
    cin >> radius;

    if (radius != 0)
        gauss(pix, width, height, radius);

    // записываем данные в новый файл
    new_img.write(reinterpret_cast<char*>(&header), sizeof(header));
    new_img.write(reinterpret_cast<char*>(pix.data()), pix.size() * 3);

    cout << "Изображение успешно в файле 'new_img.bmp'." << endl;

    img.close();
    new_img.close();
    
    return 0;
}