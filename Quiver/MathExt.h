#ifndef MATH_EXT_H_INCLUDED
#define MATH_EXT_H_INCLUDED

#include <math.h>
#include <float.h>

    /// float comparator (0: x != y, 1: x = y)
#define CMP(x, y) \
    fabsf((x) - (y)) <= FLT_EPSILON * \
    fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))) \

double DTR(double deg);
double RTD(double rad);

#endif // MATH_EXT_H_INCLUDED
