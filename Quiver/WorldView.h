#ifndef WORLDVIEW_H
#define WORLDVIEW_H

//------------------------------------------

#include <GL/freeglut.h>

//------------------------------------------

void myInit(int wWidth, int wHeight);
void physics();
void renderPlayerPos(void);
void display(void);
void reShape(GLsizei w, GLsizei h);
void update(void);
void getDeltaTime(void);
void setCamera(void);
void setLight(void);
void setMenu(void);
void setOrthographicProjection(void);
void unSetOrthoProjection(void);
void renderBitmapString(float x, float y, void *font, char *string);
void onKeyPress(unsigned char key, int x, int y);
void onKeyRelease(unsigned char key, int x, int y);
void mouseMove(int x, int y);
void userPosition(void);
void timer(int t);
void menuLoad(void);

#endif // WORLDVIEW_H
