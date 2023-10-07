#pragma once
#include <cstdint>
#include <vector>

struct pixel_struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

#pragma pack(push, 1)
struct BMPHeader{
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

void rotate_right(std::vector<pixel_struct> &pix, BMPHeader &header);