#include "Model.h"

OFFObj3d *loadOFFObj(const char *nFile) {
    OFFObj3d * obj = (OFFObj3d *)malloc(sizeof(OFFObj3d));
    readOFFFile(obj, nFile);
    objNormalise(obj);

    findRadiusPerFace(obj);

    return obj;
}

void drawOFFObj(const OFFObj3d *coord) {
    for(int i = 0;i < coord->nFace;++i) {
        Face f;

        f.x = coord->faceCoord[i].x;
        f.y = coord->faceCoord[i].y;
        f.z = coord->faceCoord[i].z;

        glBegin(GL_TRIANGLES);
            glVertex3f(coord->vertCoord[f.x].x,
                       coord->vertCoord[f.x].y,
                       coord->vertCoord[f.x].z
                      );
            glVertex3f(coord->vertCoord[f.y].x,
                       coord->vertCoord[f.y].y,
                       coord->vertCoord[f.y].z
                      );
            glVertex3f(coord->vertCoord[f.z].x,
                       coord->vertCoord[f.z].y,
                       coord->vertCoord[f.z].z
                      );
        glEnd();
    }
}

void allocGObjectMem(GameObject *gObject) {
    gObject->position = (point3D *)malloc(gObject->numObjects * sizeof(point3D));
}

void freeGObjectMem(GameObject *gObject) {
    free(gObject->position);
}
