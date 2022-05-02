#include "OffData.h"
#include "ReadFile.h"

#ifndef OBJECTS_H
#define OBJECTS_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define DEG2RAD M_PI/180.0

typedef GLfloat point3[3];

void drawGround(void);
void drawMenu2D(int wWidth, int wHeight);
void drawTargetInnerRing(void);
void drawTargetSecondRing(void);
void drawTargetThirdRing(void);
void drawTargetOuterRing(void);
void drawTarget(void);
void drawTargetWithLegs(void);
void boxTarget(void);
void draw5BoxTarget(void);
void drawSun(float sunAlt);
void drawFence(void);
void drawFenceArea(void);
void drawWindArrow(void);
void drawTree1(void);
void drawTree2(void);
void drawWallDoor(void);
void drawWall(void);
void drawRoof(void);
void drawHouseInterior(void);
void drawHouse(void);

#endif // OBJECTS_H
