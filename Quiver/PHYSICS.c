//------------------------------------------------------------------------

#include "PHYSICS.h"
#include "MATH_EXT.h"
#include <stdlib.h>

//------------------------------------------------------------------------

Vec3 _passiveForce = {0, -9.81f, 0};

AABB beamPosXLow = {(Vec3){4.75, -0.5, -18.7}, (Vec3){0.075, 0.075, 16.0}};
AABB beamPosXHigh = {(Vec3){4.75, -0.1, -18.7}, (Vec3){0.075, 0.075, 16.0}};
AABB beamNegXLow = {(Vec3){-7.25, -0.5, -18.7}, (Vec3){0.075, 0.075, 16.0}};
AABB beamNegXHigh = {(Vec3){-7.25, -0.1, -18.7}, (Vec3){0.075, 0.075, 16.0}};
AABB beamMidLow = {(Vec3){-1.25, -0.5, -34.7}, (Vec3){6.0, 0.075, 0.075}};
AABB beamMidHigh = {(Vec3){-1.25, -0.1, -34.7}, (Vec3){6.0, 0.075, 0.075}};
AABB postPosX = {(Vec3){4.75, -0.5, -0.7}, (Vec3){0.1, 0.5, 0.1}};
AABB postNegX = {(Vec3){-7.25, -0.5, -0.7}, (Vec3){0.1, 0.5, 0.1}};
AABB postMid = {(Vec3){-7.25, -0.5, -0.7}, (Vec3){0.1, 0.5, 0.1}};

//------------------------------------------------------------------------

void step(Object * obj, float dt);
void UpdateRotation(Object * O);
void ColliderPointPlane(Object* O, const Plane* P);
Vec3 GetAABBSize(const Vec3* min, const Vec3* max);

//------------------------------------------------------------------------

void SetPassiveForce(const Vec3* F)
{
    _passiveForce = *F;
}

void UpdatePhysics(Object* O, const Plane* ground, const ListAABB* listAABB, float dt)
{
    dt /= 1000;

    step(O, dt);

    UpdateRotation(O);

    for (unsigned i = 0; i < listAABB->size; ++i){
        if (PointInAABB(&O->position, &listAABB->arr[i]))
        O->isStatic = 1;
    }

    if ((PointInAABB(&O->position, &beamPosXLow))
        ||
        (PointInAABB(&O->position, &beamPosXHigh))
        ||
        (PointInAABB(&O->position, &beamNegXLow))
        ||
        (PointInAABB(&O->position, &beamNegXHigh))
        ||
        (PointInAABB(&O->position, &beamMidLow))
        ||
        (PointInAABB(&O->position, &beamMidHigh)))
    O->isStatic = 1;

    AABB tempPostPos = postPosX;
    AABB tempPostNeg = postNegX;
    AABB tempPostMid = postMid;

    for (unsigned i = 0; i < 17; ++i) {
        tempPostPos.position.z = postPosX.position.z - 2*(i+1);
        tempPostNeg.position.z = postNegX.position.z - 2*(i+1);

        if (PointInAABB(&O->position, &tempPostPos))
            O->isStatic = 1;
        if (PointInAABB(&O->position, &tempPostNeg))
            O->isStatic = 1;
    }

    for (unsigned i = 0; i < 5; ++i) {
        tempPostMid.position.x = postMid.position.x - 2*(i+1);
        if (PointInAABB(&O->position, &tempPostMid))
            O->isStatic = 1;
    }

    if (PlaneEquation(&O->position, ground) < 0.0f)
        O->isStatic = 1;
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
    float coldistance = 0.01f;
    Vec3 closestPoint = ClosestPointPlane(P, &O->position);
    Vec3 planeToPoint = Sub(&O->position, &closestPoint);

    if(LengthSQ(&planeToPoint) < coldistance * coldistance)
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
