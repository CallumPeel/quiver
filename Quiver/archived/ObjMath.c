#include "ObjMath.h"

vector3D *scalar(vector3D *firstVec, double nScalar) {
    firstVec->x *= nScalar;
    firstVec->y *= nScalar;
    firstVec->z *= nScalar;

    return firstVec;
}

vector3D *crossProduct(vector3D *vecA, vector3D *vecB) {
    vector3D *finalVec = (vector3D *)malloc(sizeof(vector3D));

    finalVec->x = (vecA->y * vecB->z) - (vecA->z * vecB->y);
    finalVec->y = (vecA->z * vecB->x) - (vecA->x * vecB->z);
    finalVec->z = (vecA->x * vecB->y) - (vecA->y * vecB->x);

    return finalVec;
}

double dotProduct(vector3D *vecA, vector3D *vecB) {
    return ((vecA->x * vecB->x) +
                (vecA->y * vecB->y) +
                (vecA->z * vecB->z));
}

vector3D *subtractVector3D(vector3D *vecA, vector3D *vecB) {
    vector3D *totalVec = (vector3D *)malloc(sizeof(vector3D));

    totalVec->x = vecA->x - vecB->x;
    totalVec->y = vecA->y - vecB->y;
    totalVec->z = vecA->z - vecB->z;

    return totalVec;
}

double magnitude(vector3D *vecA) {
    return sqrt(pow(vecA->x, 2) + pow(vecA->y, 2) + pow(vecA->z, 2));
}

double magnitude1(double vecA[]) {
    return sqrt(pow(vecA[0], 2) + pow(vecA[1], 2) + pow(vecA[2], 2));
}
