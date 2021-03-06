#ifndef MODEL_H
#define MODEL_H

#include "OffData.h"
#include "ReadFile.h"
#include "VECTORS.h"

// Change this to include point3s
typedef struct BoundingBox {
    GLfloat minX, maxX, minY, maxY, minZ, maxZ;
}BoundingBox;

typedef struct GameObject {
    point3D *position;
    BoundingBox box;
    OFFObj3d* obj;
} GameObject;

OFFObj3d *loadOFFObj(const char *nFile);

void drawOFFObj(GameObject coord);
void drawBoundingBox(GameObject model);

void allocGObjectMem(GameObject *gObject);
void freeGObjectMem(GameObject *gObject);
BoundingBox getBoundingBox(OFFObj3d model);

//void rotateBoundingBox(GameObject* obj, double pitch, double roll, double yaw);
void rotateModel(GameObject* obj, double pitch, double roll, double yaw);

#endif // MODEL_H

