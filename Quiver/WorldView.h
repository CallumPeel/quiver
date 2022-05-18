#ifndef WORLDVIEW_H
#define WORLDVIEW_H

//------------------------------------------------------------------------

#include <freeglut.h>
#include "Objects.h"
#include "Collision.h"
#include "ObjMath.h"
#include "RenderObject.h"

//------------------------------------------------------------------------

//  *** NEEDS COMMENTING ***

void initializeModels();
void InitDefaults();
void Display(void);
void Reshape(int w, int h);
void KeyDown(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);
void Mouse(int x, int y);
void Clock(int t);

//------------------------------------------------------------------------

#endif // WORLDVIEW_H
