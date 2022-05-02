#ifndef OBJECTS_H
#define OBJECTS_H

//------------------------------------------

#include "OffData.h"
#include "ReadFile.h"

//------------------------------------------

typedef GLfloat point3[3];

//------------------------------------------

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
