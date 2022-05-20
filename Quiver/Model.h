#ifndef MODEL_H
#define MODEL_H

#include "OffData.h"
#include "ReadFile.h"
#include "VECTORS.h"

// Change this to include point3s
typedef struct BoundingBox {
    point3D a,b,c,d,e,f,g,h;
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

#endif // MODEL_H

