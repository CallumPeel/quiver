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
    glLineWidth(0.1);
    // Front Face
    glBegin(GL_LINE_LOOP);
    glVertex3f(model.box.minX + model.position->x, model.box.maxY + model.position->y, model.box.minZ + model.position->z);
    glVertex3f(model.box.minX + model.position->x, model.box.minY + model.position->y, model.box.minZ + model.position->z);
    glVertex3f(model.box.maxX + model.position->x, model.box.minY + model.position->y, model.box.minZ + model.position->z);
    glVertex3f(model.box.maxX + model.position->x, model.box.maxY + model.position->y, model.box.minZ + model.position->z);
    glEnd();
    // Top Face
    glBegin(GL_LINE_LOOP);
    glVertex3f(model.box.minX + model.position->x, model.box.maxY + model.position->y, model.box.minZ + model.position->z);
    glVertex3f(model.box.minX + model.position->x, model.box.maxY + model.position->y, model.box.maxZ + model.position->z);
    glVertex3f(model.box.maxX + model.position->x, model.box.maxY + model.position->y, model.box.maxZ + model.position->z);
    glVertex3f(model.box.maxX + model.position->x, model.box.maxY + model.position->y, model.box.minZ + model.position->z);
    glEnd();
    // Bottom Face
    glBegin(GL_LINE_LOOP);
    glVertex3f(model.box.minX + model.position->x, model.box.minY + model.position->y, model.box.maxZ + model.position->z);
    glVertex3f(model.box.minX + model.position->x, model.box.minY + model.position->y, model.box.minZ + model.position->z);
    glVertex3f(model.box.maxX + model.position->x, model.box.minY + model.position->y, model.box.minZ + model.position->z);
    glVertex3f(model.box.maxX + model.position->x, model.box.minY + model.position->y, model.box.maxZ + model.position->z);
    glEnd();
    // Left Face
    glBegin(GL_LINE_LOOP);
    glVertex3f(model.box.minX + model.position->x, model.box.maxY + model.position->y, model.box.minZ + model.position->z);
    glVertex3f(model.box.minX + model.position->x, model.box.minY + model.position->y, model.box.minZ + model.position->z);
    glVertex3f(model.box.minX + model.position->x, model.box.minY + model.position->y, model.box.maxZ + model.position->z);
    glVertex3f(model.box.minX + model.position->x, model.box.maxY + model.position->y, model.box.maxZ + model.position->z);
    glEnd();
    // Right Face
    glBegin(GL_LINE_LOOP);
    glVertex3f(model.box.maxX + model.position->x, model.box.maxY + model.position->y, model.box.minZ + model.position->z);
    glVertex3f(model.box.maxX + model.position->x, model.box.minY + model.position->y, model.box.minZ + model.position->z);
    glVertex3f(model.box.maxX + model.position->x, model.box.minY + model.position->y, model.box.maxZ + model.position->z);
    glVertex3f(model.box.maxX + model.position->x, model.box.maxY + model.position->y, model.box.maxZ + model.position->z);
    glEnd();
    // Back Face
    glBegin(GL_LINE_LOOP);
    glVertex3f(model.box.maxX + model.position->x, model.box.maxY + model.position->y, model.box.maxZ + model.position->z);
    glVertex3f(model.box.maxX + model.position->x, model.box.minY + model.position->y, model.box.maxZ + model.position->z);
    glVertex3f(model.box.minX + model.position->x, model.box.minY + model.position->y, model.box.maxZ + model.position->z);
    glVertex3f(model.box.minX + model.position->x, model.box.maxY + model.position->y, model.box.maxZ + model.position->z);
    glEnd();
}

void allocGObjectMem(GameObject *gObject) {
    gObject->position = (point3D *)malloc(gObject->numObjects * sizeof(point3D));
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

