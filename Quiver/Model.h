#ifndef MODEL_H
#define MODEL_H

//------------------------------------------

#include "OffData.h"
#include "ReadFile.h"

//------------------------------------------

typedef struct GameObject {
    int numObjects;
    point3D *position;
} GameObject;

OFFObj3d *loadOFFObj(const char *nFile);

void drawOFFObj(const OFFObj3d *coord);

void allocGObjectMem(GameObject *gObject);
void freeGObjectMem(GameObject *gObject);

#endif // MODEL_H

