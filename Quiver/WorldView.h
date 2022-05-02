#include <GL/freeglut.h>
#include "Objects.h"
#include "Collision.h"
#include "ObjMath.h"
#include "RenderObject.h"

#ifndef WORLDVIEW_H
#define WORLDVIEW_H
//polygon mode
#define POLYFILL TRUE
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define DEG2RAD M_PI/180.0

void myInit(int wWidth, int wHeight);
//void physics();
void renderPlayerPos(void);
void display(void);
void reShape(GLsizei w, GLsizei h);
void update(void);
void getDeltaTime(void);
void setCamera(void);
void setLight(void);
void setMenu(void);
void set3DOrthoProjection(void);
void unSet3DOrthoProjection(void);
void renderBitmapString(float x, float y, void *font, char *string);
void onKeyPress(unsigned char key, int x, int y);
void onKeyRelease(unsigned char key, int x, int y);
void mouseMove(int x, int y);
void userPosition(void);
void timer(int t);
void menuLoad(void);

#endif // WORLDVIEW_H
