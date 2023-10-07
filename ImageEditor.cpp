#include <iostream>
#include <fstream>
#include <vector>

// files for rotation, blurring, and messages in the console
#include "rotate.h"
#include "rotate.cpp"
#include "Gauss_blur.h"
#include "Gauss_blur.cpp"
#include "Ui logic.h"

using namespace std;

int main() {
    // file initialization
    cout << "Enter file name (without .bmp): ";
    string file_name;

    cin >> file_name;
    file_name = "C://CODE//C++//ImageEditor//" + file_name + ".bmp";

    ifstream img(file_name, ios::binary);
    ofstream new_img("C://CODE//C++//ImageEditor//new_img.bmp", ios::binary | ios::trunc);

    // checking for the correctness of the input
    if (!img.is_open()) {
        cout << "Error with oppening file" << endl;
        return 0;
    }

    // working with the header
    BMPHeader header;
    img.read(reinterpret_cast<char*>(&header), sizeof(header));

    int width = header.width;
    int height = header.height;

    // pixel storage vector
    vector<pixel_struct> pix(width * height);

    img.read(reinterpret_cast<char*>(pix.data()), pix.size() * 3);

    int ui_command[2];
    gui(ui_command);

    if (ui_command[0] == 1)
        rotate_right(pix, header);
    else if (ui_command[0] == 2)
        rotate_left(pix, header);
    if (ui_command[1] != 0)
        gauss(pix, width, height, ui_command[1]);

    // writing the data to a new file
    new_img.write(reinterpret_cast<char*>(&header), sizeof(header));
    new_img.write(reinterpret_cast<char*>(pix.data()), pix.size() * 3);

    cout << "Image succelful write in 'new_img.bmp'." << endl;

    img.close();
    new_img.close();
    
    return 0;
}