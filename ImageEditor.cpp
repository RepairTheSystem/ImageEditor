#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#pragma pack(1);
struct header_struct{
    uint16_t signature;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t byte_to_pix;
    uint32_t header_size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bits_per_pix;
    uint32_t compression;
    uint32_t data_size;
    int32_t horizontal_resolution;
    int32_t vertical_resolution;
    uint32_t colors;
    uint32_t important_colors;
};
#pragma pack();

/* void fill_header(ifstream& img, fstream& new_img){

}
 */

int main (){
    ifstream img("C://CODE//C++//ImageEditor//3.bmp", ios::binary);
    fstream new_img("new_img.bmp", ios::binary | ios::trunc | ios::out | ios::in);

    if (!img.is_open() or !new_img.is_open()){
        cout << "Не удалось открыть файл";

        return 0;
    }
    else{
        cout << "удалось прочитать изображение" << endl;

        header_struct header;
        img.read(reinterpret_cast<char *>(&header), sizeof(header));
        
        int32_t new_width = header.height;
        int32_t new_height = header.width;
        int32_t row_size = (new_width * header.bits_per_pix + 31) / 8;

        vector<uint8_t> buffer(row_size, 0);

        header_struct new_header = header;
        new_header.width = new_width;
        new_header.height = new_height;
        new_header.file_size = row_size * new_height + new_header.byte_to_pix;

        new_img.write(reinterpret_cast<char*> (&new_header), sizeof(new_header));

        for (int32_t y = 0; y < header.height; ++y) {
            int32_t newRow = header.height - y - 1;
            for (int32_t x = 0; x < header.width; ++x) {
                img.read(reinterpret_cast<char*>(&buffer[0]), row_size);
                new_img.write(reinterpret_cast<char*>(&buffer[0]), row_size);
            }
        }
        new_img.close();
        img.close();
    }

    return 0;
}