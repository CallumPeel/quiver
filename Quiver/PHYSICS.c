//------------------------------------------------------------------------

#include "PHYSICS.h"
#include "MATH_EXT.h"

//------------------------------------------------------------------------

Vec3 _passiveForce = {0, -9.81f, 0};

//------------------------------------------------------------------------

void step(Object * obj, float dt);
void UpdateRotation(Object * O);
void ColliderPointPlane(Object * O, Plane const * P);

//------------------------------------------------------------------------

void SetPassiveForce(const Vec3* F)
{
    _passiveForce = *F;
}

void UpdatePhysics(Object* arrow, ArrPlane* P, float dt)
{
    dt /= 1000;

    step(arrow, dt);

    UpdateRotation(arrow);

    for (unsigned i = 0; i < P->size; ++i)
        ColliderPointPlane(arrow, &P->planes[i]);
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

void ColliderPointPlane(Object * O, Plane const * P)
{
    float coldistance = 0.09f;
    Vec3 closestPointPlane = ClosestPointPlane(P, &O->position);
    Vec3 planeToPoint = Sub(&O->position, &closestPointPlane);

    if(Length_squared(&planeToPoint) < coldistance * coldistance)
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

void InitObject(Object* O, float mass, unsigned isStatic)
{
    Vec3 zero = {0, 0, 0};

    O->position = zero;
    O->velocity = zero;
    O->force = zero;
    O->rotation = zero;
    O->mass = mass;
    O->isStatic = isStatic;
}
