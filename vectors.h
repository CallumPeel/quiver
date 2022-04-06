#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

#include <math.h>

typedef struct { double x, y, z; } vec;

vec Zero(void);
vec Neg(vec const * v);
vec Add(vec const * u, vec const * v);
vec Sub(vec const * u, vec const * v);
vec Mul(vec const * u, double const fac);
vec Div(vec const * u, double const fac);

double Length(vec const * v);
double Length_squared(vec const * v);
vec Normalize(vec const * v);

double dot(vec const * u, vec const * v);
vec cross(vec const * u, vec const * v);

#endif // MATH_H_INCLUDED
