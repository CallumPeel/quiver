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
        glVertex3d(model.box.e.x, model.box.e.y, model.box.e.z);
        glVertex3d(model.box.a.x, model.box.a.y, model.box.a.z);
        glVertex3d(model.box.d.x, model.box.d.y, model.box.d.z);
        glVertex3d(model.box.h.x, model.box.h.y, model.box.h.z);
        glEnd();
        // Top Face
        glBegin(GL_LINE_LOOP);
        glVertex3d(model.box.e.x, model.box.e.y, model.box.e.z);
        glVertex3d(model.box.h.x, model.box.h.y, model.box.h.z);
        glVertex3d(model.box.g.x, model.box.g.y, model.box.g.z);
        glVertex3d(model.box.f.x, model.box.f.y, model.box.f.z);
        glEnd();
        // Bottom Face
        glBegin(GL_LINE_LOOP);
        glVertex3d(model.box.a.x, model.box.a.y, model.box.a.z);
        glVertex3d(model.box.d.x, model.box.d.y, model.box.d.z);
        glVertex3d(model.box.c.x, model.box.c.y, model.box.c.z);
        glVertex3d(model.box.b.x, model.box.b.y, model.box.b.z);
        glEnd();
        // Left Face
        glBegin(GL_LINE_LOOP);
        glVertex3d(model.box.e.x, model.box.e.y, model.box.e.z);
        glVertex3d(model.box.a.x, model.box.a.y, model.box.a.z);
        glVertex3d(model.box.b.x, model.box.b.y, model.box.b.z);
        glVertex3d(model.box.f.x, model.box.f.y, model.box.f.z);
        glEnd();
        // Right Face
        glBegin(GL_LINE_LOOP);
        glVertex3d(model.box.h.x, model.box.h.y, model.box.h.z);
        glVertex3d(model.box.d.x, model.box.d.y, model.box.d.z);
        glVertex3d(model.box.c.x, model.box.c.y, model.box.c.z);
        glVertex3d(model.box.g.x, model.box.g.y, model.box.g.z);
        glEnd();
        // Back Face
        glBegin(GL_LINE_LOOP);
        glVertex3d(model.box.f.x, model.box.f.y, model.box.f.z);
        glVertex3d(model.box.b.x, model.box.b.y, model.box.b.z);
        glVertex3d(model.box.c.x, model.box.c.y, model.box.c.z);
        glVertex3d(model.box.g.x, model.box.g.y, model.box.g.z);
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
    BoundingBox box = { 0,0,0,0,0,0,0,0 };
    double minX = 0, maxX = 0, maxY = 0, minY = 0, minZ = 0, maxZ = 0;

    point3D temp;
    for (int i = 0; i < model.nVert; i++) {
        temp = model.vertCoord[i];
        if (temp.x < minX) minX = temp.x;
        if (temp.x > maxX) maxX = temp.x;
        if (temp.y > maxY) maxY = temp.y;
        if (temp.y < minY) minY = temp.y;
        if (temp.z < minZ) minZ = temp.z;
        if (temp.z > maxZ) maxZ = temp.z;
    }
    // Top
    box.a.x = minX;
    box.a.y = minY;
    box.a.z = minZ;

    box.b.x = minX;
    box.b.y = minY;
    box.b.z = maxZ;

    box.c.x = maxX;
    box.c.y = minY;
    box.c.z = maxZ;

    box.d.x = maxX;
    box.d.y = minY;
    box.d.z = minZ;

    // Bottom
    box.e.x = minX;
    box.e.y = maxY;
    box.e.z = minZ;

    box.f.x = minX;
    box.f.y = maxY;
    box.f.z = maxZ;

    box.g.x = maxX;
    box.g.y = maxY;
    box.g.z = maxZ;

    box.h.x = maxX;
    box.h.y = maxY;
    box.h.z = minZ;


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

void rotateBoundingBox(GameObject* gameObj, double pitch, double roll, double yaw) {
    BoundingBox temp = { 0,0,0,0,0,0,0,0 };
    temp.a = rotate(gameObj->box.a, pitch, roll, yaw);
    temp.b = rotate(gameObj->box.b, pitch, roll, yaw);
    temp.c = rotate(gameObj->box.c, pitch, roll, yaw);
    temp.d = rotate(gameObj->box.d, pitch, roll, yaw);
    temp.e = rotate(gameObj->box.e, pitch, roll, yaw);
    temp.f = rotate(gameObj->box.f, pitch, roll, yaw);
    temp.g = rotate(gameObj->box.g, pitch, roll, yaw);
    temp.h = rotate(gameObj->box.h, pitch, roll, yaw);
    gameObj->box = temp;
}
