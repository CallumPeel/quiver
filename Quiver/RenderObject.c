#include "RenderObject.h"
#include "Model.h"
#include "Objects.h"

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
void renderTargets(double targetWithLegs[3][3]) {
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
