#ifndef OBJMATH_H
#define OBJMATH_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct point3D {
    double x;
    double y;
    double z;
} point3D;

typedef point3D vector3D;

vector3D *scalar(vector3D *firstVec, double nScalar);

vector3D *crossProduct(vector3D *vecA, vector3D *vecB);

double dotProduct(vector3D *vecA, vector3D *vecB);

vector3D *subtractVector3D(vector3D *vecA, vector3D *vecB);

double magnitude(vector3D *vecA);

double magnitude1(double vecA[]);

#endif // OBJMATH_H
