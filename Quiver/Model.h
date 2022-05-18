#ifndef MODEL_H
#define MODEL_H

#include "OffData.h"
#include "ReadFile.h"

typedef struct BoundingBox {
    GLfloat minX, maxX, minY, maxY, minZ, maxZ;
}BoundingBox;

typedef struct GameObject {
    int numObjects;
    point3D *position;
    BoundingBox box;
} GameObject;

OFFObj3d *loadOFFObj(const char *nFile);

void drawOFFObj(const OFFObj3d *coord);

void allocGObjectMem(GameObject *gObject);
void freeGObjectMem(GameObject *gObject);
BoundingBox getBoundingBox(OFFObj3d model);

#endif // MODEL_H

