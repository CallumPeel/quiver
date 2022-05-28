#ifndef PHYSICS_H
#define PHYSICS_H

//------------------------------------------------------------------------

#include "Geometry3D.h"

//------------------------------------------------------------------------

typedef struct Object {
    Vec3 position,
         velocity,
         force,
         rotation; // as degrees (yaw, pitch, roll)
    float mass;
    unsigned isStatic;
} Object;

typedef struct ArrPlane {
    unsigned size;
    Plane* planes;
} ArrPlane;

typedef struct ArrAABB {
    unsigned size;
    AABB* aabbs;
} ArrAABB;

//------------------------------------------------------------------------

void SetPassiveForce(const Vec3* F);

void UpdatePhysics(Object* arrow, ArrPlane* planes, float dt);

void ShootArrow(Object* arrow, const Vec3* pos, const Vec3* dir, float force);

void InitObject(Object* O, float mass, unsigned isStatic);

//------------------------------------------------------------------------

#endif // PHYSICS_H
