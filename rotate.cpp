#include "rotate.h"

// function to rotate the image 90 degrees clockwise
void rotate_right(std::vector<pixel_struct>& pix, BMPHeader &header) {
    std::vector<pixel_struct> rotated_pix(pix.size());
    int width = header.width;
    int height = header.height;

    // symmetrically reflect each pixel
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int new_x = y;
            int new_y = width - x - 1;
            
            int original_index = y * width + x;
            int new_index = new_y * height + new_x;
            
            rotated_pix[new_index] = pix[original_index];
        }
    }
    // changing the header parameters for the new file
    header.width = height;
    header.height = width;

    // updating the pixel array
    pix = rotated_pix;
}
// function to rotate the image 90 degrees counterclockwise
void rotate_left(std::vector<pixel_struct>& pix, BMPHeader &header) {
    std::vector<pixel_struct> rotated_pix(pix.size());
    int width = header.width;
    int height = header.height;

    // symmetrically reflect each pixel
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int new_x = height - y - 1;
            int new_y = x;

            int original_index = y * width + x;
            int new_index = new_y * height + new_x;

            rotated_pix[new_index] = pix[original_index];
        }
    } 
    // changing the header parameters for the new file
    header.width = height;
    header.height = width;

    // updating the pixel array
    pix = rotated_pix;
}
