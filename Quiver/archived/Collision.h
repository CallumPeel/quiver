#ifndef COLLISION_H
#define COLLISION_H

#include "OffData.h"
#include "ObjMath.h"
#include "Model.h"

int isCollidingForTwo(GameObject objA, GameObject* objB);
int isColliding(GameObject arrow, GameObject** objectList, int numObjs);

#endif // COLLISION_H
