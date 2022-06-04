#ifndef WORLDVIEW_H
#define WORLDVIEW_H

//------------------------------------------------------------------------

#include <freeglut.h>
#include "Camera.h"
#include "PHYSICS.h"
#include "OFF.h"
#include "SCENE.h"
#include <stb_image.h>
#include "ImageProcessor.h"
#include <time.h>

//------------------------------------------------------------------------

//  *** NEEDS COMMENTING ***

void Init();
void Display(void);
void Reshape(int w, int h);
void KeyDown(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);
void Mouse(int x, int y);
void Clock(int t);
void onMouseClick(int button, int state, int x, int y);
void specialKeyPressed(int key, int x, int y);
void pullString(void);
void BowPosition(Camera const * cam);

//------------------------------------------------------------------------

#endif // WORLDVIEW_H
