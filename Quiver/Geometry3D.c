#include "Geometry3D.h"
#include "MATH_EXT.h"

//------------------------------------------------------------------------
// LINES

bool PointOnLine(Vec3 const * point, Line const * line)
{
    Vec3 closest = ClosestPointLine(line, point);
    Vec3 diff = Sub(&closest, point);
    float magsq = Length_squared(&diff);

    return CMP(magsq, 0.0f);
}

Vec3 ClosestPointLine(Line const * line, Vec3 const * point)
{
    Vec3 linevec = Sub(&line->end, line->start);
    Vec3 pointstart = Sub(point, line->start);
    float t = Dot(&pointstart, &linevec) / Length_squared(&linevec);
    t = fmaxf(t, 0.0f); // clamp to 0;
    t = fminf(t, 1.0f); // clamp to 1;
    linevec = Mul(&linevec, t);

    return Add(line->start, &linevec);
}

//------------------------------------------------------------------------
// PLANES

bool PointOnPlane(Vec3 const * point, Plane const * plane)
{
    return CMP(PlaneEquation(point, plane), 0.0f);
}

float PlaneEquation (Vec3 const * point, Plane const * plane)
{
    return Dot(point, &plane->normal) - plane->distance;
}

Vec3 ClosestPointPlane(Plane const * plane, Vec3 const * point)
{
    float dot = Dot(&plane->normal, point);
    float distance = dot - plane->distance;
    Vec3 v = Mul(&plane->normal, distance);

    return Sub(point, &v);
}

//------------------------------------------------------------------------
// SPHERES

bool PointInSphere(Vec3 const * point, Sphere const * sphere)
{
    Vec3 v = Sub(point, sphere->position);
    float magsq = Length_squared(&v);
    float radsq = sphere->radius * sphere->radius;

    return magsq < radsq;
}

Vec3 ClosestPointSphere(Sphere const * sphere, Vec3 const * point)
{
    Vec3 sphereToPoint = Sub(point, sphere->position);
    Normalize(&sphereToPoint);
    sphereToPoint = Mul(&sphereToPoint, sphere->radius);

    return Add(&sphereToPoint, sphere->position);
}

bool SpherePlane(Sphere const * sphere, Plane const * plane)
{
    Vec3 closest = ClosestPointPlane(plane, sphere->position);
    Vec3 closestToCenter = Sub(sphere->position, &closest);
    float magsq = Length_squared(&closestToCenter);
    float radsq = sphere->radius * sphere->radius;
    return magsq < radsq;
}

//------------------------------------------------------------------------
// AXIS ALIGNED BOUNDING BOXES

Vec3 GetMin(AABB const * aabb)
{
    Vec3 p1 = Add(&aabb->position, &aabb->size);
    Vec3 p2 = Sub(&aabb->position, &aabb->size);

    return (Vec3){fminf(p1.x, p2.x),
                  fminf(p1.y, p2.y),
                  fminf(p1.z, p2.z)};
}

Vec3 GetMax(AABB const * aabb)
{
    Vec3 p1 = Add(&aabb->position, &aabb->size);
    Vec3 p2 = Sub(&aabb->position, &aabb->size);

    return (Vec3){fmaxf(p1.x, p2.x),
                  fmaxf(p1.y, p2.y),
                  fmaxf(p1.z, p2.z)};
}

AABB FromMinMax(Vec3 const * min, Vec3 const * max)
{
    AABB aabb;

    aabb.position = Add(min, max);
    aabb.position = Mul(&aabb.position, 0.5f);
    aabb.size = Sub(max, min);
    aabb.size = Mul(&aabb.size, 0.5f);

    return aabb;
}

bool PointInAABB(Vec3 const * point, AABB const * aabb)
{
    Vec3 min = GetMin(aabb);
    Vec3 max = GetMax(aabb);

    if (point->x < min.x || point->y < min.y || point->z < min.z)
        return false;
    if (point->x > max.x || point->y > max.y || point->z > max.z)
        return false;

    return true;
}

Vec3 ClosestPointAABB(AABB const * aabb, Vec3 const * point)
{
    Vec3 result = *point;
    Vec3 min = GetMin(aabb);
    Vec3 max = GetMax(aabb);

    result.x = (result.x < min.x) ? min.x : result.x;
    result.y = (result.y < min.y) ? min.y : result.y;
    result.z = (result.z < min.z) ? min.z : result.z;

    result.x = (result.x > max.x) ? max.x : result.x;
    result.y = (result.y > max.y) ? max.y : result.y;
    result.z = (result.z > max.z) ? max.z : result.z;

    return result;
}

//------------------------------------------------------------------------
