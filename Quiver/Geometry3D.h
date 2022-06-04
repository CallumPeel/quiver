#ifndef GEOMETRY3D_H
#define GEOMETRY3D_H

//------------------------------------------------------------------------
// LIBRARIES

#include "Vectors.h"
#include <stdbool.h>
#include "MathExt.h"

//------------------------------------------------------------------------
// STRUCT DEFINES

typedef struct Line {
    Vec3 const * start;
    Vec3 end;
} Line;

typedef struct Plane {
    Vec3 normal;
    float distance;
} Plane;

typedef struct Sphere {
    Vec3 const * position;
    float radius;
} Sphere;

typedef struct AABB {
    Vec3 position;
    Vec3 size;
} AABB;

//------------------------------------------------------------------------
// LINES

bool PointOnLine(Vec3 const * point, Line const * line);

Vec3 ClosestPointLine(Line const * line, Vec3 const * point);

//------------------------------------------------------------------------
// PLANES

bool PointOnPlane(Vec3 const * point, Plane const * plane);

float PlaneEquation(Vec3 const * point, Plane const * plane);

Vec3 ClosestPointPlane(Plane const * plane, Vec3 const * point);

//------------------------------------------------------------------------
// SPHERES

bool PointInSphere(Vec3 const * point, Sphere const * sphere);

Vec3 ClosestPointSphere(Sphere const * sphere, Vec3 const * point);

bool SpherePlane(Sphere const * sphere, Plane const * plane);

//------------------------------------------------------------------------
// AXIS ALIGNED BOUNDING BOXES

Vec3 GetMin(AABB const * aabb);

Vec3 GetMax(AABB const * aabb);

AABB FromMinMax(Vec3 const * min, Vec3 const * max);

bool PointInAABB(Vec3 const * point, AABB const * aabb);

Vec3 ClosestPointAABB(AABB const * aabb, Vec3 const * point);

//------------------------------------------------------------------------

#endif // GEOMETRY3D_H
