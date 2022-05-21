#include "Model.h"

OFFObj3d *loadOFFObj(const char *nFile) {
    OFFObj3d * obj = (OFFObj3d *)malloc(sizeof(OFFObj3d));
    readOFFFile(obj, nFile);
    objNormalise(obj);

    findRadiusPerFace(obj);

    return obj;
}

void drawOFFObj(GameObject gameObj) {
    glPushMatrix();
    glRotated(gameObj.obj->rot->x, 1, 0, 0);
    glRotated(gameObj.obj->rot->y, 0, 1, 0);
    glRotated(gameObj.obj->rot->z, 0, 0, 1);
        glTranslated(gameObj.position->x, gameObj.position->y, gameObj.position->z);

        for(int i = 0;i < gameObj.obj->nFace;++i) {
            Face f;

            f.x = gameObj.obj->faceCoord[i].x;
            f.y = gameObj.obj->faceCoord[i].y;
            f.z = gameObj.obj->faceCoord[i].z;

            glBegin(GL_TRIANGLES);
                glVertex3f(gameObj.obj->vertCoord[f.x].x,
                           gameObj.obj->vertCoord[f.x].y,
                           gameObj.obj->vertCoord[f.x].z
                          );
                glVertex3f(gameObj.obj->vertCoord[f.y].x,
                           gameObj.obj->vertCoord[f.y].y,
                           gameObj.obj->vertCoord[f.y].z
                          );
                glVertex3f(gameObj.obj->vertCoord[f.z].x,
                           gameObj.obj->vertCoord[f.z].y,
                           gameObj.obj->vertCoord[f.z].z
                          );
            glEnd();
        }
    glPopMatrix();
}

void drawBoundingBox(GameObject model) {
    glPushMatrix();
        glTranslated(model.position->x, model.position->y, model.position->z);
        glLineWidth(0.1);
        // Front Face
        glBegin(GL_LINE_LOOP);
        glVertex3f(model.box.minX, model.box.maxY, model.box.minZ);
        glVertex3f(model.box.minX, model.box.minY, model.box.minZ);
        glVertex3f(model.box.maxX, model.box.minY, model.box.minZ);
        glVertex3f(model.box.maxX, model.box.maxY, model.box.minZ);
        glEnd();
        // Top Face
        glBegin(GL_LINE_LOOP);
        glVertex3f(model.box.minX, model.box.maxY, model.box.minZ);
        glVertex3f(model.box.minX, model.box.maxY, model.box.maxZ);
        glVertex3f(model.box.maxX, model.box.maxY, model.box.maxZ);
        glVertex3f(model.box.maxX, model.box.maxY, model.box.minZ);
        glEnd();
        // Bottom Face
        glBegin(GL_LINE_LOOP);
        glVertex3f(model.box.minX, model.box.minY, model.box.maxZ);
        glVertex3f(model.box.minX, model.box.minY, model.box.minZ);
        glVertex3f(model.box.maxX, model.box.minY, model.box.minZ);
        glVertex3f(model.box.maxX, model.box.minY, model.box.maxZ);
        glEnd();
        // Left Face
        glBegin(GL_LINE_LOOP);
        glVertex3f(model.box.minX, model.box.maxY, model.box.minZ);
        glVertex3f(model.box.minX, model.box.minY, model.box.minZ);
        glVertex3f(model.box.minX, model.box.minY, model.box.maxZ);
        glVertex3f(model.box.minX, model.box.maxY, model.box.maxZ);
        glEnd();
        // Right Face
        glBegin(GL_LINE_LOOP);
        glVertex3f(model.box.maxX, model.box.maxY, model.box.minZ);
        glVertex3f(model.box.maxX, model.box.minY, model.box.minZ);
        glVertex3f(model.box.maxX, model.box.minY, model.box.maxZ);
        glVertex3f(model.box.maxX, model.box.maxY, model.box.maxZ);
        glEnd();
        // Back Face
        glBegin(GL_LINE_LOOP);
        glVertex3f(model.box.maxX, model.box.maxY, model.box.maxZ);
        glVertex3f(model.box.maxX, model.box.minY, model.box.maxZ);
        glVertex3f(model.box.minX, model.box.minY, model.box.maxZ);
        glVertex3f(model.box.minX, model.box.maxY, model.box.maxZ);
        glEnd();
    glPopMatrix();
}

void allocGObjectMem(GameObject *gObject) {
    gObject->position = (point3D *)malloc(sizeof(point3D));
    gObject->obj = (OFFObj3d *)malloc(sizeof(OFFObj3d));
}

void freeGObjectMem(GameObject *gObject) {
    free(gObject->position);
}

BoundingBox getBoundingBox(OFFObj3d model) {
    BoundingBox box = { 0,0,0,0,0,0 };
    point3D temp;
    for (int i = 0; i < model.nVert; i++) {
        temp = model.vertCoord[i];
        if (temp.x < box.minX) box.minX = temp.x;
        if (temp.x > box.maxX) box.maxX = temp.x;
        if (temp.y > box.maxY) box.maxY = temp.y;
        if (temp.y < box.minY) box.minY = temp.y;
        if (temp.z < box.minZ) box.minZ = temp.z;
        if (temp.z > box.maxZ) box.maxZ = temp.z;
    }
    return box;
}

point3D rotate(point3D point, double pitch, double roll, double yaw) {
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

    double px = point.x;
    double py = point.y;
    double pz = point.z;

    point.x = Axx * px + Axy * py + Axz * pz;
    point.y = Ayx * px + Ayy * py + Ayz * pz;
    point.z = Azx * px + Azy * py + Azz * pz;

    return point;
}

void rotateModel(GameObject* gameObj, double pitch, double roll, double yaw) {
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

    for (int i = 0; i < gameObj->obj->nVert; i++) {
        double px = gameObj->obj->vertCoord[i].x;
        double py = gameObj->obj->vertCoord[i].y;
        double pz = gameObj->obj->vertCoord[i].z;

        gameObj->obj->vertCoord[i].x = Axx * px + Axy * py + Axz * pz;
        gameObj->obj->vertCoord[i].y = Ayx * px + Ayy * py + Ayz * pz;
        gameObj->obj->vertCoord[i].z = Azx * px + Azy * py + Azz * pz;
    }
    gameObj->box = getBoundingBox(*gameObj->obj);
}
