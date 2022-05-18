#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "Model.h"
#include "Objects.h"

void drawBone(GameObject boneObj);
void renderGround(void);
void renderSun(double sunAngle);
void renderTrees(void);
void renderFences(void);
void renderTargets(double targetWithLegs[3][3]);
void renderHouses(void);

#endif // RENDEROBJECT_H
