//------------------------------------------------------------------------

#include "PHYSICS.h"
#include "MATH_EXT.h"
#include <stdlib.h>

//------------------------------------------------------------------------

Vec3 _passiveForce = {0, -9.81f, 0};

//------------------------------------------------------------------------

void step(Object * obj, float dt);
void UpdateRotation(Object * O);
void ColliderPointPlane(Object* O, const Plane* P);
void ColliderPointAABB(Object* O, const AABB* A);

//------------------------------------------------------------------------

Vec3 GetAABBSize(const Vec3* min, const Vec3* max);

//------------------------------------------------------------------------

void SetPassiveForce(const Vec3* F)
{
    _passiveForce = *F;
}

void UpdatePhysics(Object* arrow, const Plane* ground, const ListAABB* listAABB, float dt)
{
    dt /= 1000;

    step(arrow, dt);

    UpdateRotation(arrow);

    for (unsigned i = 0; i < listAABB->size; ++i)
        ColliderPointAABB(arrow, &listAABB->arr[i]);

    ColliderPointPlane(arrow, ground);
}

void step(Object* obj, float dt)
{
    if (obj->isStatic) return;

    Vec3 f = Mul(&_passiveForce, obj->mass);
    obj->force = Add(&obj->force, &f);

    Vec3 v = Div(&obj->force, obj->mass);
    v = Mul(&v, dt);
    obj->velocity = Add(&obj->velocity, &v);

    Vec3 p = Mul(&obj->velocity, dt);
    obj->position = Add(&obj->position, &p);

    obj->force = (Vec3){0, 0, 0};
}

void ColliderPointPlane(Object* O, const Plane* P)
{
    float coldistance = 0.09f;
    Vec3 closestPoint = ClosestPointPlane(P, &O->position);
    Vec3 planeToPoint = Sub(&O->position, &closestPoint);

    if(Length_squared(&planeToPoint) < coldistance * coldistance)
        O->isStatic = 1;
}

void ColliderPointAABB(Object* O, const AABB* A)
{
    float coldistance = 0.09f;
    Vec3 closestPoint = ClosestPointAABB(A, &O->position);
    Vec3 AABBToPoint = Sub(&O->position, &closestPoint);

    if(Length_squared(&AABBToPoint) < coldistance * coldistance)
        O->isStatic = 1;
}

void UpdateRotation(Object* O)
{
    Vec3 v = Normalize(&O->velocity);

    float yaw = atan(v.x/v.z);          // finds the angle from (0,0,-1) about y
    if (v.z > 0) yaw = yaw + M_PI;      // reflects xz rotation in +z space
    float pitch = asin(v.y);            // finds the angle from (0,0,-1) about x

    O->rotation.x = RTD(yaw);
    O->rotation.y = RTD(pitch);
}

void ShootArrow(Object* arrow, const Vec3* pos, const Vec3* dir, float force)
{
    arrow->position = *pos;
    arrow->velocity = (Vec3){0, 0, 0};
    arrow->force = Mul(dir, force);
    arrow->isStatic = 0;
}

void InitObject(Object* O, Vec3 scale, float mass)
{
    Vec3 zero = {0, 0, 0};

    O->position = zero;
    O->velocity = zero;
    O->force = zero;
    O->rotation = zero;
    O->scale = scale;
    O->mass = mass;
    O->isStatic = 1;
}

void InitListAABB(ListAABB* listaabb, const unsigned size)
{
    listaabb->size = size;
    listaabb->arr = malloc(sizeof(AABB) * size);
}

Vec3 GetOffAABBSize(const Off* off)
{
    Vec3 zero = (Vec3){0.0, 0.0, 0.0};
    Vec3 min, max;
    min = max = zero;

    for (int i = 0; i < off->nverts; i++) {
        if (off->verts[i].x < min.x) min.x = off->verts[i].x;
        else
        if (off->verts[i].x > max.x) max.x = off->verts[i].x;

        if (off->verts[i].y < min.y) min.y = off->verts[i].y;
        else
        if (off->verts[i].y > max.y) max.y = off->verts[i].y;

        if (off->verts[i].z < min.z) min.z = off->verts[i].z;
        else
        if (off->verts[i].z > max.z) max.z = off->verts[i].z;
    }

    return GetAABBSize(&min, &max);
}

Vec3 GetAABBSize(const Vec3* min, const Vec3* max)
{
    Vec3 size;

    size = Sub(max, min);
    size = Div(&size, 2.0f);

    return size;
}
