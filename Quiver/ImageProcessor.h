#ifndef IMAGEPROCESSOR_H_INCLUDED
#define IMAGEPROCESSOR_H_INCLUDED

#include <stdlib.h> //REMOVE WHEN ADDED TO WORLD VIEW
#include <stdio.h>
#include <stdint.h>
#include <freeglut.h>

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
