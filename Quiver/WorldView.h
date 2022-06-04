#ifndef WORLDVIEW_H
#define WORLDVIEW_H

//------------------------------------------------------------------------

#include <freeglut.h>

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

//------------------------------------------------------------------------

#endif // WORLDVIEW_H
