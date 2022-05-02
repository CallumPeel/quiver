#ifndef COLLISION_H
#define COLLISION_H

#include "OffData.h"
#include "ObjMath.h"

int checkCollision(double objPos1[], double objPos2[], point3D pnt1, point3D pnt2);
int collider(OFFObj3d *obj1, OFFObj3d *obj2, double objPos1[], double objPos2[]);

#endif // COLLISION_H
