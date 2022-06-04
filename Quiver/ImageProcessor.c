#include "ImageProcessor.h"
#include "CAMERA.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void loadImage(Image * img, const char * filename) {
    stbi_set_flip_vertically_on_load(1);
    img->data = stbi_load(filename, &img->width, &img->height, &img->channels, 3);

    if(img->data) {
        img->size = img->width * img->height * img->channels;
    } else {
        printf("Failed to read image");
    }
}

void freeImage(Image * img) {
    if(img->data) {
        stbi_image_free(img->data);
        img->data = NULL;
        img->width = 0;
        img->height = 0;
        img->size = 0;
    }
}

void displayImage(Image * img) {

    glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glutReshapeWindow(img->width, img->height);
    glViewport(0, 0, img->width, img->height);

    gluOrtho2D(0.0, 500, 0.0, 800);

	glMatrixMode(GL_MODELVIEW);

    glRasterPos2i(0, 0);
    glDrawPixels(img->width, img->height, GL_RGB, GL_UNSIGNED_BYTE, img->data);
}
