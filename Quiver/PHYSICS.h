#ifndef PHYSICS_H
#define PHYSICS_H

//------------------------------------------------------------------------

#include "Geometry3D.h"
#include "Off.h"
#include "MathExt.h"
#include <stdlib.h>

//------------------------------------------------------------------------

typedef struct Object {
    Vec3 position,
         velocity,
         force,
         rotation, // as degrees (yaw, pitch, roll)
         scale;
    float mass;
    unsigned isStatic;
} Object;

typedef struct ListAABB {
    unsigned size;
    AABB* arr;
} ListAABB;

//------------------------------------------------------------------------

void SetPassiveForce(const Vec3* F);

void UpdatePhysics(Object* arrow, const Plane* Ground, const ListAABB* listAABB, float dt);

void ShootArrow(Object* arrow, const Vec3* pos, const Vec3* dir, float force);

void InitObject(Object* O, Vec3 scale, float mass);

void InitListAABB(ListAABB* listaabb, const unsigned size);

Vec3 GetOffAABBSize(const Off* off);

#endif // PHYSICS_H
