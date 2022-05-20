#include "OffData.h"

/** @brief Assign memory to the size of nVert, nFace, nEdge
 */
void allocCoordMem(OFFObj3d *fileCoords) {
    if(fileCoords->nVert >= 1)
        fileCoords->vertCoord = (point3D *)malloc(fileCoords->nVert * sizeof(point3D));

    if(fileCoords->nFace >= 1)
        fileCoords->faceCoord = (Face *)malloc(fileCoords->nFace * sizeof(Face));

    fileCoords->com = (point3D *)malloc(sizeof(point3D));
    fileCoords->rad = (point3D *)malloc(fileCoords->nFace * sizeof(point3D));
}

/** @brief Free memory assigned to fileCoords
 */
void freeCoords(OFFObj3d *fileCoords) {
    free(fileCoords->vertCoord);
    free(fileCoords->faceCoord);
    free(fileCoords->com);
    free(fileCoords->rad);
}

point3D *calcCenterOfMass(const OFFObj3d *fileCoords) {
    point3D *c = (point3D *)malloc(sizeof(point3D));

    c->x = 0.0;
    c->y = 0.0;
    c->z = 0.0;

    for(int i = 0;i < fileCoords->nVert;++i) {
        c->x += fileCoords->vertCoord[i].x;
        c->y += fileCoords->vertCoord[i].y;
        c->z += fileCoords->vertCoord[i].z;
    }

    c->x /= fileCoords->nVert;
    c->y /= fileCoords->nVert;
    c->z /= fileCoords->nVert;

    return c;
}

double findRadius(const OFFObj3d *fileCoords, const point3D *c) {
    vector3D *mag = (point3D *)malloc(sizeof(point3D));
    double rad = 0.0;
    double maxRad = 0.0;

    for(int i = 0;i < fileCoords->nVert;++i) {
        mag->x = fileCoords->vertCoord[i].x - c->x;
        mag->y = fileCoords->vertCoord[i].y - c->y;
        mag->z = fileCoords->vertCoord[i].z - c->z;

        rad = magnitude(mag);

        if(rad > maxRad)
            maxRad = rad;
    }

    free(mag);

    return maxRad;
}

void findRadiusPerFace(OFFObj3d *fileCoords) {
    point3D *mag = (point3D *)malloc(fileCoords->nFace * sizeof(point3D));

    for(int i = 0;i < fileCoords->nFace;++i) {
        Face f;

        f.x = fileCoords->faceCoord[i].x;
        f.y = fileCoords->faceCoord[i].y;
        f.z = fileCoords->faceCoord[i].z;

        mag[i].x = (fileCoords->vertCoord[f.x].x + fileCoords->vertCoord[f.y].x + fileCoords->vertCoord[f.z].x) / 3;
        mag[i].y = (fileCoords->vertCoord[f.x].y + fileCoords->vertCoord[f.y].y + fileCoords->vertCoord[f.z].y) / 3;
        mag[i].z = (fileCoords->vertCoord[f.x].z + fileCoords->vertCoord[f.y].z + fileCoords->vertCoord[f.z].z) / 3;
    }

    fileCoords->rad = mag;

    free(mag);
}

void objNormalise(OFFObj3d *fileCoords) {
    const point3D *com = calcCenterOfMass(fileCoords);
    const double rad = findRadius(fileCoords, com);

    for(int i = 0;i < fileCoords->nVert;++i) {
        fileCoords->vertCoord[i].x = (fileCoords->vertCoord[i].x - com->x) / rad;
        fileCoords->vertCoord[i].y = (fileCoords->vertCoord[i].y - com->y) / rad;
        fileCoords->vertCoord[i].z = (fileCoords->vertCoord[i].z - com->z) / rad;
    }

    free((point3D *)com);
}

void rotateModel(OFFObj3d* obj, double pitch, double roll, double yaw) {
    double cosa = cos(yaw);
    double sina = sin(yaw);

    double cosb = cos(pitch);
    double sinb = sin(pitch);

    double cosc = cos(roll);
    double sinc = sin(roll);

    double Axx = cosa * cosb;
    double Axy = cosa * sinb * sinc - sina * cosc;
    double Axz = cosa * sinb * cosc + sina * sinc;

    double Ayx = sina * cosb;
    double Ayy = sina * sinb * sinc + cosa * cosc;
    double Ayz = sina * sinb * cosc - cosa * sinc;

    double Azx = -sinb;
    double Azy = cosb * sinc;
    double Azz = cosb * cosc;

    for (int i = 0; i < obj->nVert; i++) {
        double px = obj->vertCoord[i].x;
        double py = obj->vertCoord[i].y;
        double pz = obj->vertCoord[i].z;

        obj->vertCoord[i].x = Axx * px + Axy * py + Axz * pz;
        obj->vertCoord[i].y = Ayx * px + Ayy * py + Ayz * pz;
        obj->vertCoord[i].z = Azx * px + Azy * py + Azz * pz;
    }
}
