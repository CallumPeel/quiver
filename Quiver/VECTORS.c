#include "VECTORS.h"
#include <math.h>

Vec3 Neg(Vec3 const * v) {
    return (Vec3) {
        -v->x,
        -v->y,
        -v->z
    };
}

Vec3 Add(Vec3 const * u, Vec3 const * v) {
    return (Vec3) {
        u->x + v->x,
        u->y + v->y,
        u->z + v->z
    };
}

Vec3 Sub(Vec3 const * u, Vec3 const * v) {
    Vec3 w = Neg(v);
    return Add( u, &w );
}

Vec3 Mul(Vec3 const * u, double const fac) {
    return (Vec3) {
        u->x * fac,
        u->y * fac,
        u->z * fac
    };
}
Vec3 Div(Vec3 const * u, double const fac) {
    return Mul( u, 1.0f/fac );
}

double Dot(Vec3 const * u, Vec3 const * v) {
    return u->x * v->x + u->y * v->y + u->z * v->z;
}

Vec3 Cross(Vec3 const * u, Vec3 const * v) {
    return (Vec3) {
        u->y * v->z - u->z * v->y,
        u->z * v->x - u->x * v->z,
        u->x * v->y - u->y * v->x
    };
}

double Length(Vec3 const * v) {
    return sqrt(LengthSQ(v));
}

double LengthSQ(Vec3 const * v){
    return Dot(v, v);
}

Vec3 Normalize(Vec3 const * v) {
    return Div(v, Length(v));
}

Vec3 Reflect(Vec3 const * v, Vec3 const * n)
{
    float d = Dot(v, n);

    Vec3 result = Mul(n, d * 2.0f);
    result = Sub(v, &result);

    return result;
}
