#ifndef IMAGEPROCESSOR_H_INCLUDED
#define IMAGEPROCESSOR_H_INCLUDED

#include <stdint.h>
#include "WorldView.h"

typedef struct {
    int width;
    int height;
    int channels;
    size_t size;
    uint8_t * data;
} Image;

void loadImage(Image * img, const char * filename);

void freeImage(Image * img);

void displayImage(Image * img);

#endif
