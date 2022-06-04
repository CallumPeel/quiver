#include "Menu.h"

//------------------------------------------------------------------------

int _menu = 0;
void *font = GLUT_BITMAP_TIMES_ROMAN_24;

//------------------------------------------------------------------------

void RenderBitmapString(float x, float y, void *font, char *string) {
    char *c;
    glRasterPos2d(x, y);

    for (c=string; *c != '\0'; c++) {
        if(*c == '\n') {
            y+=30;
            glRasterPos2d(x-5, y);
            glutBitmapCharacter(font, *c);
        } else {
            glutBitmapCharacter(font, *c);
        }
    }
}

void drawMenu2D(int wWidth, int wHeight) {
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(wWidth-10, wHeight-10);
        glVertex2f(10, 10);
        glVertex2f(10, wHeight-10);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(wWidth-10, wHeight-10);
        glVertex2f(wWidth-10, 10);
        glVertex2f(10, 10);
    glEnd();
}

void Set3DOrtho() {
    // switch to projection mode
    glMatrixMode(GL_PROJECTION);

    //save projection mode settings
    glPushMatrix();

    // reset matrix
    glLoadIdentity();

    ///SetPerspective();

    // switch back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}

void UnSet3DOrtho(void) {
    // switch to projection mode
    glMatrixMode(GL_PROJECTION);

    ///SetPerspective();

    glPopMatrix();

    // switch back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}

void set2DOrthoProjection(void) {
    // switch to projection mode
    glMatrixMode(GL_PROJECTION);

    //save projection mode settings
    glPushMatrix();

    // reset matrix
    glLoadIdentity();

    // load a 2d orthographic projection
    ///gluOrtho2D(0, winx, winy, 0);

    // switch back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}

void unSet2DOrthoProjection(void) {
    // switch to projection mode
    glMatrixMode(GL_PROJECTION);

    //SetPerspective();

    glPopMatrix();

    // switch back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}

void ShowMenu(void) {
    if(_menu) {
        _menu = 0;
        set2DOrthoProjection();
        glLoadIdentity();
        glColor3ub(128, 128, 128);
        RenderBitmapString(20, 30, font, "This\nis\nthe\nmenu");
        ///drawMenu2D(winx, winy);
        unSet2DOrthoProjection();
    }
    else {
        _menu = 1;
    }
}
