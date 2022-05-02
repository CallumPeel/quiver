#include "WorldView.h"
#include "Objects.h"
#include "Collision.h"
#include "ObjMath.h"
#include "RenderObject.h"

//------------------------------------------

//window resizing ratio
double wr = 1.0f;

/* window size */
int wW = 950, wH = 700;
int fps = 120;

//------------------------------------------

            /* User Position */

double vertAngle = 0.0f;
double horizAngle = 0.0f;
float lx = 0.0f, lz = 0.0f, ly = 1.0f;
double xPos = 0;
double yPos = 0;
double zPos = 0;
double forwardMove = 0;
double sideMove = 0;

//------------------------------------------

            /* movement speed */

double speed = 1.0f;
double mSpeed = 0.05f;

//------------------------------------------

GLboolean menu = GL_FALSE;

void *font = GLUT_BITMAP_TIMES_ROMAN_24;

//------------------------------------------

            /* object positions */

double targetWithLegs[3][3] = {
    {1.5f, 0.0f, -30.0f}, //object 1
    {-3.0f, 0.0f, 0.0f}, //object 2
    {-3.0f, 0.0f, 0.0f} //object 3
}; 
float sunAngle = 0.0f;

//------------------------------------------

            /* Camera variables */

const GLdouble camPerspect[] = {
    60.0, 1.0, //pov, aspect
    0.1, 200   //near, far
};

//------------------------------------------

int flag = 0;
double angle = 90.0;
double dirX = 0.0;
double dirZ = 0.0;
float deltaTime = 0.0f;
float initTime = 0.0f;
float currTimeA = 0.0;

//------------------------------------------

void myInit(int ww, int wh) {
    //Change to Projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glClearColor(0, 0.5, 1, 1.0f);
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(1.0);

    if(POLYFILL)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    setCamera();

    glMatrixMode(GL_MODELVIEW);

    wW = ww;
    wH = wh;
}

void getDeltaTime() {
    GLfloat frameTime;

    frameTime = glutGet(GLUT_ELAPSED_TIME);

    deltaTime = (frameTime - initTime) / 1000;

    initTime = frameTime;
}

void update() {
    sunAngle += deltaTime * 0.36;

    if(sunAngle >= 360) sunAngle = 0;
}

void setLight(void){
		// Define RGBA specular colours for object material
		GLfloat  mat_specular[]  =  {1.0, 1.0, 1.0, 1.0 };
		GLfloat  light_position[] =  {1.0, 1.0, 1.0, 0.0 };
        GLfloat  lmodel_ambient[] =  {0.2, 0.2, 0.2, 1.0 };
		// How shiny material is
		GLfloat  mat_shininess[] =  {50.0};

        // Define position of light source
        glLightfv (GL_LIGHT0, GL_POSITION, light_position);

        // Define lighting model
        glLightModelfv (GL_LIGHT_MODEL_AMBIENT,  lmodel_ambient);

        // Define material properties
        glMaterialfv (GL_FRONT, GL_SPECULAR,   mat_specular);
        glMaterialfv (GL_FRONT, GL_SHININESS,  mat_shininess);

        glEnable(GL_COLOR_MATERIAL);

        glShadeModel(GL_SMOOTH);
        //Enable lighting
        glEnable (GL_LIGHTING); // as in turn on power for
        //all lights
        glEnable (GL_LIGHT0); // as in flip on the light switch
}

void setCamera(void) {
    gluPerspective(camPerspect[0], wr,
                    camPerspect[2], camPerspect[3]);
}

void set3DOrthoProjection() {
    // switch to projection mode
    glMatrixMode(GL_PROJECTION);

    //save projection mode settings
    glPushMatrix();

    // reset matrix
    glLoadIdentity();

    setCamera();

    // switch back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}

void unSet3DOrthoProjection(void) {
    // switch to projection mode
    glMatrixMode(GL_PROJECTION);

    setCamera();

    glPopMatrix();

    // switch back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}

void windArrow() {
    if(!menu) {
        set3DOrthoProjection();

        glPushMatrix();
            glTranslatef(-0.1, 0.05, -0.2);
            glRotated(-horizAngle+angle, 0, 1, 0);
            glScalef(0.05, 0.05, 0.05);
            drawWindArrow();
        glPopMatrix();

        unSet3DOrthoProjection();
        glLoadIdentity();
    }
}

void set2DOrthoProjection(void) {
    // switch to projection mode
    glMatrixMode(GL_PROJECTION);

    //save projection mode settings
    glPushMatrix();

    // reset matrix
    glLoadIdentity();

    // load a 2d orthographic projection
    gluOrtho2D(0, wW, wH, 0);

    // switch back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}

void unSet2DOrthoProjection(void) {
    // switch to projection mode
    glMatrixMode(GL_PROJECTION);

    setCamera();

    glPopMatrix();

    // switch back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}

void renderBitmapString(float x, float y, void *font, char *string) {
    char *c;
    glRasterPos2d(x, y);

    for (c=string; *c != '\0'; c++) {
        if(*c == '\n') {
            y+=30;
            glRasterPos2d(x-5, y);
            glutBitmapCharacter(font, *c);
        } else {
            glutBitmapCharacter(font, *c);
        }
    }
}

void menuLoad(void) {
    if(menu) {
        set2DOrthoProjection();

        glPushMatrix();
            glLoadIdentity();
            glColor3ub(128, 128, 128);
            renderBitmapString(20, 30, font, "menu is here\nbye\nhello\nglut");
            drawMenu2D(wW, wH);
        glPopMatrix();

        unSet2DOrthoProjection();

        glLoadIdentity();
    }
}

void renderPlayerPos() {
    glRotated(-horizAngle, 0, 1, 0);
    glRotated(vertAngle, lx, 0, lz);
    glTranslated(-xPos, 0.0, -zPos);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); /* reset transformations */

    setLight();

    glPushMatrix();
        // changes player position in scene
        renderPlayerPos();

        renderGround();
        renderSun(sunAngle);
        renderTrees();

        renderFences();
        renderTargets(targetWithLegs);
        renderHouses();
    glPopMatrix();

    windArrow();
    menuLoad();
    update();

    glutSwapBuffers();
}

void reShape(GLsizei w, GLsizei h) {
    if(h == 0)
        h = 1;

    wr = (GLfloat) w / (GLfloat) h;

    //Change to Projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h); /* set the viewport */
    setCamera(); /* set the camera perspective */

    glMatrixMode(GL_MODELVIEW);
}

void setMenu(void) {
    if(menu)
        menu = GL_FALSE;
    else
        menu = GL_TRUE;
}

void onKeyPress(unsigned char key, int x, int y) {
    switch(key){
        case 'q':
            exit(0);
            break;
        case 'h': setMenu(); break;

        case 'w': forwardMove += 1; break;
        case 's': forwardMove += -1; break;
        case 'a': sideMove += -1; break;
        case 'd': sideMove += 1; break;

        default: break;
    }
}

void onKeyRelease(unsigned char key, int x, int y) {
    switch(key){
        case 'w': forwardMove -= 1; break;
        case 's': forwardMove -= -1; break;
        case 'a': sideMove -= -1; break;
        case 'd': sideMove -= 1; break;

        default: break;
    }
}

void userPosition(void) {
    if(forwardMove){
        xPos += forwardMove * sin(-horizAngle*DEG2RAD) * 0.05f;
        zPos += forwardMove * -cos(-horizAngle*DEG2RAD) * 0.05f;
    }
    if(sideMove){
        xPos += sideMove * sin(-horizAngle*DEG2RAD + 3.14159/2) * 0.05f;
        zPos += sideMove * -cos(-horizAngle*DEG2RAD + 3.14159/2) * 0.05f;
    }

    // Redisplay the window content
    glutPostRedisplay();
}

void mouseMove(int x, int y) {
    horizAngle += mSpeed * wr * ((float)wW/2 - x);
    vertAngle += mSpeed * ((float)wH/2 - y);

    //camera direction
    lx = -cos(horizAngle*(3.14159 / 180));
    lz = sin(horizAngle*(3.14159 / 180));

    // max angles reset
    if(horizAngle < -360) horizAngle = 0;
    if(horizAngle > 360) horizAngle = 0;
    if(vertAngle >= 90) vertAngle = 90;
    if(vertAngle <= -90) vertAngle = -90;

    glutWarpPointer(wW/2, wH/2);

    // Redisplay the window content
    glutPostRedisplay();
}

void timer(int t) {
    glutTimerFunc(1000/fps, timer, 0);

    userPosition();
    getDeltaTime();

    glutPostRedisplay();
}
