#include "SCENE.h"
#include <freeglut.h>
#include <math.h>
#include <stdio.h>


//------------------------------------------------------------------------

typedef GLfloat point3[3];
float _sunAngle = 0.0f;

//------------------------------------------------------------------------

void LoadOff(Off** offList, const char* filename)
{
    char buff[20];
    unsigned count = 0;
    FILE* lptr = fopen(filename, "r");

    while(fgets(buff, 20, lptr)) {
        if (buff[strlen(buff)-1] == '\n')
            buff[strlen(buff)-1] = '\0';
        FILE* optr = fopen(buff, "r");

        *offList = realloc(*offList, sizeof(Off) * (count+1));
        ReadOffFile(*offList+count, buff);
        NormOff(*offList+count);

        fclose(optr);

        buff[0] = '\0';
        ++count;
    }

    fclose(lptr);
}

void DrawStatic(const Static* model, Vec3 color)
{
    glColor3f(color.x, color.y, color.z);
    glTranslatef(model->aabb->position.x, model->aabb->position.y, model->aabb->position.z);
    glScalef(model->scale, model->scale, model->scale);
    DrawOff(model->off);
}

void DrawArrow(const Arrow* model)
{
    glColor3f(1.0, 0, 0);
    glPushMatrix();
        glTranslatef(model->obj.position.x,
                     model->obj.position.y,
                     model->obj.position.z);
        glRotatef(model->obj.rotation.x, 0, 1.0f, 0);
        glRotatef(model->obj.rotation.y, 1.0f, 0, 0);
        glScalef(model->obj.scale.x, model->obj.scale.y, model->obj.scale.z);
        glTranslatef(model->offset.x, model->offset.y, model->offset.z); // moves the center
        DrawOff(model->off);
    glPopMatrix();
}

void DrawOff(const Off* off)
{
    for (unsigned i = 0; i < off->nfaces; ++i){
        glBegin(GL_TRIANGLES);
            glVertex3d(
                off->verts[ off->faces[i].a ].x,
                off->verts[ off->faces[i].a ].y,
                off->verts[ off->faces[i].a ].z
            );
            glVertex3d(
                off->verts[ off->faces[i].b ].x,
                off->verts[ off->faces[i].b ].y,
                off->verts[ off->faces[i].b ].z
            );
            glVertex3d(
                off->verts[ off->faces[i].c ].x,
                off->verts[ off->faces[i].c ].y,
                off->verts[ off->faces[i].c ].z
            );
        glEnd();
    }
}

void DrawSizeBox(const Vec3* size)
{
    Vec3 points[24];

    points[0] = (Vec3){size->x, size->y, size->z};
    points[1] = (Vec3){size->x, size->y, -size->z};
    points[2] = (Vec3){size->x, -size->y, size->z};
    points[3] = (Vec3){size->x, -size->y, -size->z};

    points[4] = (Vec3){-size->x, size->y, size->z};
    points[5] = (Vec3){-size->x, size->y, -size->z};
    points[6] = (Vec3){-size->x, -size->y, size->z};
    points[7] = (Vec3){-size->x, -size->y, -size->z};

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_LINE_LOOP);
        glVertex3f(points[0].x, points[0].y, points[0].z);
        glVertex3f(points[1].x, points[1].y, points[1].z);
        glVertex3f(points[3].x, points[3].y, points[3].z);
        glVertex3f(points[2].x, points[2].y, points[2].z);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3f(points[4].x, points[4].y, points[4].z);
        glVertex3f(points[5].x, points[5].y, points[5].z);
        glVertex3f(points[7].x, points[7].y, points[7].z);
        glVertex3f(points[6].x, points[6].y, points[6].z);
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(points[0].x, points[0].y, points[0].z);
        glVertex3f(points[4].x, points[4].y, points[4].z);
        glVertex3f(points[1].x, points[1].y, points[1].z);
        glVertex3f(points[5].x, points[5].y, points[5].z);
        glVertex3f(points[3].x, points[3].y, points[3].z);
        glVertex3f(points[7].x, points[7].y, points[7].z);
        glVertex3f(points[2].x, points[2].y, points[2].z);
        glVertex3f(points[6].x, points[6].y, points[6].z);
    glEnd();
}

void DrawScene()
{
    renderSun();
    renderGround();
    renderTrees();
    renderFences();
    renderTargets();
    renderHouses();
}

void AddSunAngle(float angle)
{
    _sunAngle = fmod(_sunAngle + angle, 360.0f);
}

// display ground
void renderGround() {
    glPushMatrix();
        glTranslated(-55.0f, -1.0f, -15.0f);
        glScaled(25, 1, 25);
        drawGround();
    glPopMatrix();
}

// display sun
void renderSun(double sunAngle) {
    glPushMatrix();
        drawSun(sunAngle);
    glPopMatrix();
}

// display all trees
void renderTrees() {
    glPushMatrix();
        glPushMatrix();
            glTranslated(-11, -1, 0);
            for(int i = 0;i < 5;++i) {
                glTranslated(0, 0, -7);
                drawTree1();
            }
        glPopMatrix();

        glPushMatrix();
            glTranslated(8.5, -1, 0);
            for(int i = 0;i < 5;++i) {
                glTranslated(0, 0, -7);
                drawTree2();
            }
        glPopMatrix();
    glPopMatrix();
}

// display all fences
void renderFences() {
    glPushMatrix();
        for(int i = 0;i < 3; ++i) {
            if(i == 0)
                glTranslated(-20, 0, 0);
            else
                glTranslated(20, 0, 0);
            drawFenceArea();
        }
    glPopMatrix();
}

// display all targets
void renderTargets() {
    double targetWithLegs[3][3] = {
        {1.5f, 0.0f, -30.0f}, //object 1
        {-3.0f, 0.0f, 0.0f}, //object 2
        {-3.0f, 0.0f, 0.0f} //object 3
    };

    glPushMatrix();
        for(int i = 0;i < 3;++i) {
            glTranslated(targetWithLegs[i][0], targetWithLegs[i][1], targetWithLegs[i][2]);
            drawTargetWithLegs();
        }
    glPopMatrix();

    glPushMatrix();
        glTranslated(-20.0, -0.5, -20.0);
        draw5BoxTarget();
    glPopMatrix();
}

// display all houses
void renderHouses() {
    glPushMatrix();
        double loc[] = {15, -2, -20};

        for(int i = 0;i < 3;++i) {
            glColor3d(0.6, 0.5, 1.0);
            glPushMatrix();
                glTranslated(loc[i], 1.0, 3.0);
                glScaled(5.0, 3.0, 3.0);
                drawHouse();
            glPopMatrix();
        }
    glPopMatrix();
}

void drawGroundRange(void) {
    point3 grassGnd[] = {{-1.0f, 0.0f, -0.9f}, {-1.0f, 0.0f, 0.5f}, {-0.9f, 0.0f, 0.5f}, {-0.9f, 0.0f, -0.9f}};
    point3 brownBack[] = {{-1.0f, 0.0f, -0.8f}, {-1.0f, 0.0f, 0.5f}, {-0.5f, 0.0f, 0.5f}, {-0.5f, 0.0f, -0.8f}};
    point3 grayGnd[] = {{-1.0f, 0.0f, -0.9f}, {-1.0f, 0.0f, -0.8f}, {-0.4f, 0.0f, -0.8f}, {-0.4f, 0.0f, -0.9f}};
    point3 rearGrayGnd[] = {{-1.0f, 0.0f, -0.9f}, {-1.0f, 0.0f, 0.5f}, {-0.9f, 0.0f, 0.5f}, {-0.9f, 0.0f, -0.9f}};

    glPushMatrix();
        // left gray surface
        glPushMatrix();
            glColor3f(0.6f, 0.6f, 0.6f);
            glBegin(GL_QUADS);
                for(int i = 0;i < 4;++i) {
                    glVertex3fv(grassGnd[i]);
                }
            glEnd();
        glPopMatrix();

        // brown surface
        glPushMatrix();
            glTranslatef(0.1f, 0.0f, 0.0f);

            glColor3f(0.5f, 0.4f, 0.05f);
            glBegin(GL_QUADS);
                for(int i = 0;i < 4;++i) {
                    glVertex3fv(brownBack[i]);
                }
            glEnd();
        glPopMatrix();

        // rear gray surface
        glPushMatrix();
            glTranslatef(0.1f, 0.0f, 0.0f);

            glColor3f(0.6f, 0.6f, 0.6f);
            glBegin(GL_QUADS);
                for(int i = 0;i < 4;++i) {
                    glVertex3fv(grayGnd[i]);
                }
            glEnd();
        glPopMatrix();

        // right gray surface
        glPushMatrix();
            glTranslatef(0.6f, 0.0f, 0.0f);

            glColor3f(0.6f, 0.6f, 0.6f);
            glBegin(GL_QUADS);
                for(int i = 0;i < 4;++i) {
                    glVertex3fv(rearGrayGnd[i]);
                }
            glEnd();
        glPopMatrix();
    glPopMatrix();
}

void drawGround(void) {
    point3 grassArea1[] = {{-1.0f, 0.0f, -2.0f}, {-1.0f, 0.0f, 2.0f}, {1.0f, 0.0f, 2.0f}, {1.0f, 0.0f, -2.0f}};
    point3 grassArea2[] = {{-1.5f, 0.0f, -1.0f}, {-1.5f, 0.0f, 0.1f}, {1.3f, 0.0f, 0.1f}, {1.3f, 0.0f, -1.0f}};
    point3 grassArea3[] = {{-1.5f, 0.0f, -0.0f}, {-1.5f, 0.0f, 1.0f}, {1.3f, 0.0f, 1.0f}, {1.3f, 0.0f, -0.0f}};
    point3 grassArea4[] = {{-0.0f, 0.0f, -0.0f}, {-0.0f, 0.0f, 1.4f}, {0.1f, 0.0f, 1.4f}, {0.1f, 0.0f, -0.0f}};
    point3 grassArea5[] = {{-0.0f, 0.0f, -0.0f}, {-0.0f, 0.0f, 1.4f}, {0.1f, 0.0f, 1.4f}, {0.1f, 0.0f, -0.0f}};
    point3 grassArea6[] = {{-1.0f, 0.0f, -2.0f}, {-1.0, 0.0f, 2.0f}, {1.0f, 0.0f, 2.0f}, {1.0f, 0.0f, -2.0f}};
    point3 grayArea1[] = {{-1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.5f}, {1.3f, 0.0f, 0.5f}, {1.3f, 0.0f, 0.0f}};

    glPushMatrix();
        //  grass
        glPushMatrix();
            glColor3f(0.1f, 0.5f, 0.1f);
            glBegin(GL_QUADS);
                for(int i = 0;i < 4;++i) {
                    glVertex3fv(grassArea1[i]);
                }
            glEnd();
        glPopMatrix();

        //  rear grass
        glPushMatrix();
            glTranslatef(2.0f, 0.0f, -1.0f);
            glColor3f(0.1f, 0.5f, 0.1f);
            glBegin(GL_QUADS);
                for(int i = 0;i < 4;++i) {
                    glVertex3fv(grassArea2[i]);
                }
            glEnd();
        glPopMatrix();

        //  front grass
        glPushMatrix();
            glTranslatef(2.0f, 0.0f, 1.0f);
            glColor3f(0.1f, 0.5f, 0.1f);
            glBegin(GL_QUADS);
                for(int i = 0;i < 4;++i) {
                    glVertex3fv(grassArea3[i]);
                }
            glEnd();
        glPopMatrix();

        //  front gray
        glPushMatrix();
            glTranslatef(2.0f, 0.0f, 0.5);
            glColor3f(0.6f, 0.6f, 0.6f);
            glBegin(GL_QUADS);
                for(int i = 0;i < 4;++i) {
                    glVertex3fv(grayArea1[i]);
                }
            glEnd();
        glPopMatrix();

        //  grass
        glPushMatrix();
            glTranslatef(1.7f, 0.0f, -0.9f);
            glColor3f(0.1f, 0.5f, 0.1f);
            glBegin(GL_QUADS);
                for(int i = 0;i < 4;++i) {
                    glVertex3fv(grassArea4[i]);
                }
            glEnd();
        glPopMatrix();

        //  grass
        glPushMatrix();
            glTranslatef(2.5f, 0.0f, -0.9f);
            glColor3f(0.1f, 0.5f, 0.1f);
            glBegin(GL_QUADS);
                for(int i = 0;i < 4;++i) {
                    glVertex3fv(grassArea5[i]);
                }
            glEnd();
        glPopMatrix();

        glTranslatef(2.0f, 0.0f, 0.0f);
        drawGroundRange();

        glTranslatef(0.8f, 0.0f, 0.0f);
        drawGroundRange();

        glTranslatef(0.8f, 0.0f, 0.0f);
        drawGroundRange();

        // grass
        glTranslatef(0.7f, 0.0f, 0.0f);
        glPushMatrix();
            glColor3f(0.1f, 0.5f, 0.1f);
            glBegin(GL_QUADS);
                for(int i = 0;i < 4;++i) {
                    glVertex3fv(grassArea6[i]);
                }
            glEnd();
        glPopMatrix();
    glPopMatrix();
}

void drawTargetInnerRing(void) {
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glTranslatef(0.0f, 0.0f, 0.02f);
        glutSolidCylinder(0.2f, 0.08f, 30, 30);
    glPopMatrix();
}

void drawTargetSecondRing(void) {
    glPushMatrix();
        glColor3f(0.5, 0.5, 0.5);
        glTranslatef(0.0f, 0.0f, 0.01f);
        glutSolidCylinder(0.45f, 0.08f, 30, 30);
    glPopMatrix();
}

void drawTargetThirdRing(void) {
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(0.0f, 0.0f, 0.005f);
        glutSolidCylinder(0.7f, 0.08f, 30, 30);
    glPopMatrix();
}

void drawTargetOuterRing(void) {
    glPushMatrix();
        glColor3f(0.1f, 0.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, -0.05f);
        glutSolidCylinder(0.9f, 0.1f, 30, 30);
    glPopMatrix();
}

void drawTarget(void) {
    // target
    glPushMatrix();
        // inner ring
        drawTargetInnerRing();

        // second ring
        drawTargetSecondRing();

        // third ring
        drawTargetThirdRing();

        // outer ring
        drawTargetOuterRing();
    glPopMatrix();
}

void boxTarget(void) {
    drawTarget();

    glPushMatrix();
        glColor3ub(128, 128, 128);
        glTranslatef(0.0, 0.0, -0.9);
        glutSolidCube(1.8);
    glPopMatrix();
}

void draw5BoxTarget(void) {
    glPushMatrix();
        glScalef(0.1, 0.1, 0.1);

        boxTarget();

        glTranslatef(1.8, -1.8, 0.0);
        boxTarget();

        glPushMatrix();
            glColor3f(0.858824, 0.576471, 0.439216);
            glRotatef(90, 1.0, 0.0, 0.0);
            glTranslatef(0.0, -1.0, -2.7);
            glutSolidCylinder(0.25, 1.75, 20, 20);
        glPopMatrix();

        glTranslatef(0.0, 3.6, 0.0);
        boxTarget();

        glPushMatrix();
            glColor3f(0.858824, 0.576471, 0.439216);
            glRotatef(90, 0.0, 1.0, 0.0);
            glTranslatef(1.0, 0.0, -2.7);
            glutSolidCylinder(0.25, 1.75, 20, 20);
        glPopMatrix();

        glTranslatef(-3.6, 0.0, 0.0);
        boxTarget();

        glPushMatrix();
            glColor3f(0.858824, 0.576471, 0.439216);
            glRotatef(90, 1.0, 0.0, 0.0);
            glTranslatef(0.0, -1.0, 0.9);
            glutSolidCylinder(0.25, 1.75, 20, 20);
        glPopMatrix();

        glTranslatef(0.0, -3.6, 0.0);
        boxTarget();

        glPushMatrix();
            glColor3f(0.858824, 0.576471, 0.439216);
            glRotatef(90, 0.0, 1.0, 0.0);
            glTranslatef(1.0, 0.0, 0.9);
            glutSolidCylinder(0.25, 1.75, 20, 20);
        glPopMatrix();
    glPopMatrix();
}

void drawTargetWithLegs(void) {
    glPushMatrix();
        // rotate target
        glRotatef(-25, 1.0f, 0.0f, 1.0f);
        drawTarget();
    glPopMatrix();

    // legs
    glPushMatrix();
        // straighten legs
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        glRotatef(45, 0.0f, 0.0f, 1.0f);
        // leg 1
        glPushMatrix();
            glColor3f(0.5f, 0.35f, 0.05f);
            glTranslatef(-0.5f, 0.5f, 0.0f);
            glutSolidCylinder(0.05f, 1.0f, 4, 4);
        glPopMatrix();

        // leg 2
        glPushMatrix();
            glColor3f(0.5f, 0.35f, 0.05f);
            glTranslatef(0.5f, -0.54f, 0.0f);
            glutSolidCylinder(0.05f, 1.0f, 4, 4);
        glPopMatrix();
    glPopMatrix();
}

void drawSun() {
    glRotatef(180, 0, 1, 0);            // latitude
    glRotatef(-20, 0, 0, 1);            // roll
    glRotatef(_sunAngle, 1, 0, 0);      // altitude
    glTranslatef(0, 0, -100);           // displacement from camera
    glColor3f(1.0f, 1.0f, 0.0f);
    glutSolidCylinder(3, 0, 30, 30);
}

void drawFence(void) {
    glPushMatrix();
        glColor3f(0.5f, 0.35f, 0.05f);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        glutSolidCylinder(0.1, 1, 20, 20);

        glPushMatrix();
            glRotatef(90, -1.0f, 0.0f, 0.0f);
            glTranslatef(0.0, -0.1, 0.0);
            glutSolidCylinder(0.075f, 2, 20, 20);

            glTranslatef(0.0, -0.5, 0.0);
            glutSolidCylinder(0.075f, 2, 20, 20);
        glPopMatrix();
    glPopMatrix();
}

void drawFenceArea(void) {
    glPushMatrix();
        glTranslatef(4.75f, 0.0f, -2.7);

        glPushMatrix();
            glRotatef(90, 1.0f, 0.0f, 0.0f);
            glutSolidCylinder(0.1, 1, 20, 20);
        glPopMatrix();

        for(int i = 0;i < 16;++i) {
            glTranslatef(0.0f, 0.0f, -2.0);
            drawFence();
        }

        glRotatef(90, 0.0f, 1.0f, 0.0f);
        for(int i = 0;i < 6;++i) {
            glTranslatef(0.0f, 0.0f, -2.0f);
            drawFence();
        }

        glRotatef(90, 0.0f, 1.0f, 0.0f);
        for(int i = 0;i < 16;++i) {
            glTranslatef(0.0f, 0.0f, -2.0);
            drawFence();
        }
    glPopMatrix();
}

void drawWindArrow(void) {
    const point3 uppDirArr[] = {{0.0, 0.05, 0.8},
                                            {0.3, 0.05, 0.4},
                                            {0.15, 0.05, 0.4},
                                            {-0.15, 0.05, 0.4},
                                            {-0.3, 0.05, 0.4},
                                            {0.15, 0.05, 0.0},
                                            {-0.15, 0.05, 0.0}};

    const point3 lowDirArr[] = {{0.0, -0.05, 0.8},
                                            {-0.3, -0.05, 0.4},
                                            {-0.15, -0.05, 0.4},
                                            {0.15, -0.05, 0.4},
                                            {0.3, -0.05, 0.4},
                                            {-0.15, -0.05, 0.0},
                                            {0.15, -0.05, 0.0}};
    glPushMatrix();
        glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
        glTranslatef(0.0, 0.5, 0.0);

        // arrow triangle top
        glBegin(GL_TRIANGLE_FAN);
            glVertex3fv(uppDirArr[0]); // top
            glVertex3fv(uppDirArr[1]); // outer left
            glVertex3fv(uppDirArr[2]); // inner left
            glVertex3fv(uppDirArr[3]); // inner right
            glVertex3fv(uppDirArr[4]); // outer right
        glEnd();

        // arrow square top
        glBegin(GL_QUADS);
            glVertex3fv(uppDirArr[2]); // inner left
            glVertex3fv(uppDirArr[5]); // bottom left
            glVertex3fv(uppDirArr[6]); // bottom right
            glVertex3fv(uppDirArr[3]); // inner right
        glEnd();

        // arrow triangle bottom
        glBegin(GL_TRIANGLE_FAN);
            glVertex3fv(lowDirArr[0]); // top
            glVertex3fv(lowDirArr[1]); // outer left
            glVertex3fv(lowDirArr[2]); // inner left
            glVertex3fv(lowDirArr[3]); // inner right
            glVertex3fv(lowDirArr[4]); // outer right
        glEnd();

        // arrow square bottom
        glBegin(GL_QUADS);
            glVertex3fv(lowDirArr[2]); // inner left
            glVertex3fv(lowDirArr[5]); // bottom left
            glVertex3fv(lowDirArr[6]); // bottom right
            glVertex3fv(lowDirArr[3]); // inner right
        glEnd();

        // arrow sides
        glBegin(GL_QUADS);
            // right first
            glVertex3fv(uppDirArr[6]);
            glVertex3fv(lowDirArr[5]);
            glVertex3fv(lowDirArr[2]);
            glVertex3fv(uppDirArr[3]);

            // right second
            glVertex3fv(uppDirArr[3]);
            glVertex3fv(lowDirArr[2]);
            glVertex3fv(lowDirArr[1]);
            glVertex3fv(uppDirArr[4]);

            // right third
            glVertex3fv(uppDirArr[4]);
            glVertex3fv(lowDirArr[1]);
            glVertex3fv(lowDirArr[0]);
            glVertex3fv(uppDirArr[0]);

            // left third
            glVertex3fv(uppDirArr[0]);
            glVertex3fv(lowDirArr[0]);
            glVertex3fv(lowDirArr[4]);
            glVertex3fv(uppDirArr[1]);

            // left second
            glVertex3fv(uppDirArr[1]);
            glVertex3fv(lowDirArr[4]);
            glVertex3fv(lowDirArr[3]);
            glVertex3fv(uppDirArr[2]);

            // left first
            glVertex3fv(uppDirArr[2]);
            glVertex3fv(lowDirArr[3]);
            glVertex3fv(lowDirArr[6]);
            glVertex3fv(uppDirArr[5]);

            // back
            glVertex3fv(uppDirArr[5]);
            glVertex3fv(lowDirArr[6]);
            glVertex3fv(lowDirArr[5]);
            glVertex3fv(uppDirArr[6]);
        glEnd();

        // arrow outline
        glPushMatrix();
            glLineWidth(3.0);
            glBegin(GL_LINE_LOOP);
                glColor3f(0.0, 0.0, 0.0); // black colour

                glVertex3fv(uppDirArr[0]); // top
                glVertex3fv(uppDirArr[1]); // outer left
                glVertex3fv(uppDirArr[2]); // inner left
                glVertex3fv(uppDirArr[5]); // bottom left
                glVertex3fv(uppDirArr[6]); // bottom right
                glVertex3fv(uppDirArr[3]); // inner right
                glVertex3fv(uppDirArr[4]); // outer right
            glEnd();

            glBegin(GL_LINE_LOOP);
                glColor3f(0.0, 0.0, 0.0);

                glVertex3fv(lowDirArr[0]); // top
                glVertex3fv(lowDirArr[1]); // outer left
                glVertex3fv(lowDirArr[2]); // inner left
                glVertex3fv(lowDirArr[5]); // bottom left
                glVertex3fv(lowDirArr[6]); // bottom right
                glVertex3fv(lowDirArr[3]); // inner right
                glVertex3fv(lowDirArr[4]); // outer right
            glEnd();

            // arrow sides
            glBegin(GL_LINES);
                // right back
                glVertex3f(-0.15, 0.05, 0.0);
                glVertex3f(-0.15, -0.05, 0.0);

                // right inner
                glVertex3f(-0.151, -0.05, 0.39);
                glVertex3f(-0.151, 0.05, 0.39);

                // right outer
                glVertex3f(-0.3, -0.05, 0.4);
                glVertex3f(-0.3, 0.05, 0.4);

                // top
                glVertex3f(0.0, -0.05, 0.8);
                glVertex3f(0.0, 0.05, 0.8);

                // left outer
                glVertex3f(0.3, -0.05, 0.4);
                glVertex3f(0.3, 0.05, 0.4);

                // left inner
                glVertex3f(0.151, -0.05, 0.39);
                glVertex3f(0.151, 0.05, 0.39);

                // left back
                glVertex3f(0.15, -0.05, 0.0);
                glVertex3f(0.15, 0.05, 0.0);
            glEnd();
        glPopMatrix();
    glPopMatrix();
}

void drawTree1() {
    glPushMatrix();
        glColor3ub(139,69,19);
        glPushMatrix();
            glRotatef(-90, 1, 0, 0);
            glutSolidCylinder(0.3, 2, 10, 10);
        glPopMatrix();

        glColor3ub(0,100,0);
        glTranslatef(0, 2, 0);
        glPushMatrix();
            glRotatef(-90, 1, 0, 0);
            glutSolidCone(2.3, 5, 10, 10);
        glPopMatrix();
    glPopMatrix();
}

void drawTree2() {
//    int appleAmnt = 20;

    glPushMatrix();
        glColor3ub(139,69,19);
        glPushMatrix();
            glRotatef(-90, 1, 0, 0);
            glutSolidCylinder(0.3, 2, 10, 10);
        glPopMatrix();

        glColor3ub(0,100,0);
        glTranslatef(0, 2, 0);
        glPushMatrix();
            glRotatef(-90, 1, 0, 0);
            glutSolidCone(2.3, 5, 10, 10);
        glPopMatrix();

        glTranslatef(0, 3, 0);
        glPushMatrix();
            glRotatef(-90, 1, 0, 0);
            glutSolidCone(2, 4, 10, 10);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-1, -3.1, -1);
            glColor3ub(200,0,0);
            glRotatef(70, 0, 1, 0);
            for(int i = 0;i < 15;++i) {
                glTranslatef(-cos(i*0.7), 0, sin(i*0.7));
                glutSolidSphere(0.1, 10, 10);
            }

            glTranslatef(-2, 0, -2);
            glColor3ub(200,0,0);
            glRotatef(50, 0, 1, 0);
            for(int i = 0;i < 7;++i) {
                glTranslatef(-cos(i*0.9), 0, sin(i*0.9));
                glutSolidSphere(0.1, 10, 10);
            }
        glPopMatrix();
    glPopMatrix();
}

void drawWallDoor(void) {
    glPushMatrix();
        // door left wall
        glBegin(GL_QUADS);
            glVertex3d(0.25, 1.0, -1.0);
            glVertex3d(0.25, -1.0, -1.0);
            glVertex3d(1.0, -1.0,-1.0);
            glVertex3d(1.0, 1.0, -1.0);
        glEnd();

        // upper door wall
        glBegin(GL_QUADS);
            glVertex3d(0.25, 0.25, -1.0);
            glVertex3d(0.25, 1.0, -1.0);
            glVertex3d(-0.25, 1.0,-1.0);
            glVertex3d(-0.25, 0.25, -1.0);
        glEnd();

        // door right wall
        glBegin(GL_QUADS);
            glVertex3d(-0.25, -1.0, -1.0);
            glVertex3d(-0.25, 1.0, -1.0);
            glVertex3d(-1.0, 1.0,-1.0);
            glVertex3d(-1.0, -1.0, -1.0);
        glEnd();
    glPopMatrix();
}

void drawWall() {
    glBegin(GL_QUADS);
        glVertex3d(-1.0, 1.0, 1.0);
        glVertex3d(-1.0, -1.0, 1.0);
        glVertex3d(1.0, -1.0, 1.0);
        glVertex3d(1.0, 1.0, 1.0);
    glEnd();
}

void drawRoof() {
    //roof
    glPushMatrix();
        glColor3d(0.3, 0.3, 0.3);
        glBegin(GL_QUADS);
            glVertex3d(-1.0, 1.7, 0.0);
            glVertex3d(-1.0, 1.0, 1.0);
            glVertex3d(1.0, 1.0, 1.0);
            glVertex3d(1.0, 1.7, 0.0);

            glVertex3d(1.0, 1.7, 0.0);
            glVertex3d(1.0, 1.0, -1.0);
            glVertex3d(-1.0, 1.0, -1.0);
            glVertex3d(-1.0, 1.7, 0.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3d(-1.0, 1.0, 1.0);
            glVertex3d(-1.0, 1.7, 0.0);
            glVertex3d(-1.0, 1.0, -1.0);
        glEnd();

        glBegin(GL_TRIANGLES);
            glVertex3d(1.0, 1.0, -1.0);
            glVertex3d(1.0, 1.7, 0.0);
            glVertex3d(1.0, 1.0, 1.0);
        glEnd();
    glPopMatrix();
}

void drawHouseInterior() {
    glPushMatrix();
        // back wall
        glRotatef(180, 0, 1, 0);
        glPushMatrix();
            glTranslated(0.0, 0.0, -1.99);
            drawWall();
        glPopMatrix();

        // left wall
        glRotatef(90, 0, 1, 0);
        glPushMatrix();
            glTranslated(0.0, 0.0, -1.99);
            drawWall();
        glPopMatrix();

        // right wall
        glRotatef(180, 0, 1, 0);
        glPushMatrix();
            glTranslated(0.0, 0.0, -1.99);
            drawWall();
        glPopMatrix();

        // door wall
        glRotatef(-90, 0, 1, 0);
        glPushMatrix();
            glTranslated(0.0, 0.0, 0.01);
            drawWallDoor();
        glPopMatrix();

        // roof
        glRotatef(90, 1, 0, 0);
        glPushMatrix();
            glColor3d(0.7, 1.0, 1.0);
            glTranslated(0.0,0.0, -2.0);
            drawWall();
        glPopMatrix();
    glPopMatrix();
}

void drawHouse() {
    glPushMatrix();
        drawWall();

        glRotatef(90, 0, 1, 0);
        drawWall();

        glRotatef(180, 0, 1, 0);
        drawWall();

        glRotatef(-90, 0, 1, 0);
        glTranslated(0.0, 0.0, 2.0);
        drawWallDoor();

        glPushMatrix();
            glTranslated(0.0, 0.0, -2.0);
            drawRoof();
        glPopMatrix();
    glPopMatrix();

    drawHouseInterior();
}
