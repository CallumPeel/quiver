#ifndef OFFDATA_H
#define OFFDATA_H

#include <freeglut.h>
#include "ObjMath.h"

typedef struct Face {
    int x;
    int y;
    int z;
}Face;

typedef struct OFFObj3d {
    int nVert;
    int nFace;
    int nEdge;

    point3D *vertCoord;
    Face *faceCoord;
    point3D *com;
    point3D *rad;
    point3D *rot;
} OFFObj3d;

/** @brief Assign memory to the size of nVert, nFace, nEdge
 */
void allocCoordMem(OFFObj3d *fileCoords);

/** @brief Free memory assigned to fileCoords
 */
void freeCoords(OFFObj3d *fileCoords);

point3D *calcCenterOfMass(const OFFObj3d *fileCoords);

double findRadius(const OFFObj3d *fileCoords, const point3D *c);

void findRadiusPerFace(OFFObj3d *fileCoords);

void objNormalise(OFFObj3d *fileCoords);

#endif // OFFDATA_H
