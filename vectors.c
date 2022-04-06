#include "vectors.h"

vec Zero(void) {
    vec w;

    w.x = 0;
    w.y = 0;
    w.z = 0;

    return w;
}

vec Neg(vec const * v) {
    vec w;

    w.x = -v->x;
    w.y = -v->y;
    w.z = -v->z;

    return w;
}

vec Add(vec const * u, vec const * v) {
    vec w;

    w.x = u->x + v->x;
    w.y = u->y + v->y;
    w.z = u->z + v->z;

    return w;
}

vec Sub(vec const * u, vec const * v) {
    vec w = Neg(v);
    return Add( u, &w );
}

vec Mul(vec const * u, double const fac) {
    vec w;

    w.x = u->x * fac;
    w.y = u->y * fac;
    w.z = u->z * fac;

    return w;
}
vec Div(vec const * u, double const fac) {
    return Mul( u, 1.0/fac );
}

double Length(vec const * v) {
    return sqrt(Length_squared(v));
}

double Length_squared(vec const * v){
    return    pow(v->x, 2.0)
            + pow(v->y, 2.0)
            + pow(v->z, 2.0);
}

vec Normalize(vec const * v) {
    return Div(v, Length(v));
}

double dot(vec const * u, vec const * v) {
    return    u->x * v->x
            + u->y * v->y
            + u->z * v->z;
}

vec cross(vec const * u, vec const * v) {
    vec w;

    w.x = u->y * v->z - u->z * v->y;
    w.y = u->z * v->x - u->x * v->z;
    w.z = u->x * v->y - u->y * v->x;

    return w;
}
