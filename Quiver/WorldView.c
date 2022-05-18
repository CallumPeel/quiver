#include "WorldView.h"
#include "CAMERA.h"

//------------------------------------------------------------------------

Camera cam = {
    (Vec3){0, 0, 0},  // cam position
    (Vec3){0, 0, -1.0}, // cam front
    (Vec3){0, 1.0, 0},  // cam up
    0.0,                // cam yaw
    0.0                 // cam pitch
};

const GLdouble camPerspect[] = {
    60.0, 1.0, //pov, aspect
    0.1, 200   //near, far
};

double targetWithLegs[3][3] = {
    {1.5f, 0.0f, -30.0f}, //object 1
    {-3.0f, 0.0f, 0.0f}, //object 2
    {-3.0f, 0.0f, 0.0f} //object 3
};

//------------------------------------------------------------------------

int fps = 60;

int dt;

double wr = 1.0f; //window resizing ratio
int winx;
int winy;

GLboolean menu = GL_FALSE;

void *font = GLUT_BITMAP_TIMES_ROMAN_24;

float sunAngle = 0.0f;

int flag = 0;
double angle = 90.0;
double dirX = 0.0;
double dirZ = 0.0;

//------------------------------------------------------------------------

void MoveSun(void);
void SetLight(void);
void Set3DOrtho(void);
void UnSet3DOrtho(void);
void RenderBitmapString(float x, float y, void *font, char *string);
void ShowMenu(void);
void SetPerspective(void);
void GetDeltaTime(int * dt, int * old_t);


OFFObj3d* arrow;
OFFObj3d* bone;
GameObject arrowObj;
GameObject boneObj;

//------------------------------------------------------------------------

void InitDefaults() {

//    arrow = loadOFFObj("arrow.off");
    bone = loadOFFObj("bone.off");
//    allocGObjectMem(&arrowObj);
//    arrowObj.position->x = 0;
//    arrowObj.position->y = 0;
//    arrowObj.position->z = 0;
//    arrowObj.box = getBoundingBox(*arrow);

    allocGObjectMem(&boneObj);
    boneObj.position->x = 0;
    boneObj.position->y = 0;
    boneObj.position->z = -4;
    boneObj.box = getBoundingBox(*bone);


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glutSetCursor(GLUT_CURSOR_NONE);

    glClearColor(0, 0.5, 1, 1.0f);
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(1.0);

    SetPerspective();

    glMatrixMode(GL_MODELVIEW);

    CamLookSpeed = 0.125;
    CamMoveSpeed = 0.0025;
}

void MoveSun() {
    sunAngle += 0.36f * dt/1000.0f;
    if(sunAngle >= 360) sunAngle = 0;
}

void SetLight(void){
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

void SetPerspective(void) {
    gluPerspective(camPerspect[0], wr,
                    camPerspect[2], camPerspect[3]);
}

void Set3DOrtho() {
    // switch to projection mode
    glMatrixMode(GL_PROJECTION);

    //save projection mode settings
    glPushMatrix();

    // reset matrix
    glLoadIdentity();

    SetPerspective();

    // switch back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}

void UnSet3DOrtho(void) {
    // switch to projection mode
    glMatrixMode(GL_PROJECTION);

    SetPerspective();

    glPopMatrix();

    // switch back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}

void set2DOrthoProjection(void) {
    // switch to projection mode
    glMatrixMode(GL_PROJECTION);

    //save projection mode settings
    glPushMatrix();

    // reset matrix
    glLoadIdentity();

    // load a 2d orthographic projection
    gluOrtho2D(0, winx, winy, 0);

    // switch back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}

void unSet2DOrthoProjection(void) {
    // switch to projection mode
    glMatrixMode(GL_PROJECTION);

    SetPerspective();

    glPopMatrix();

    // switch back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}

void RenderBitmapString(float x, float y, void *font, char *string) {
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

void ShowMenu(void) {
    if(menu) {
        set2DOrthoProjection();

        glLoadIdentity();
        glColor3ub(128, 128, 128);
        RenderBitmapString(20, 30, font, "menu is here\nbye\nhello\nglut");
        drawMenu2D(winx, winy);

        unSet2DOrthoProjection();
    }
}

void WindArrow(Camera const * cam) {
    if(!menu) { // do not render if menu is open
        glPushMatrix();
            glTranslatef(cam->Pos.x, cam->Pos.y, cam->Pos.z); // move with cam
            glRotatef(-cam->yaw, 0, 1.0, 0);                // move with -yaw
            glRotatef(cam->pitch, 1.0, 0, 0);               // move with pitch
            glTranslatef(-0.1, 0.05, -0.2);                // move to corner
            glRotatef(cam->yaw+angle, 0, 1.0, 0);           // rotate model
            glScalef(0.05, 0.05, 0.05);                    // scale model
            drawWindArrow();                               // draw model
        glPopMatrix();
    }
}

void drawBone() {
    glPushMatrix();
        glTranslatef(0,0, boneObj.position->z);
        drawOFFObj(bone);
    glPopMatrix();
}


void Display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); /* reset transformations */

    LookAt(&cam);

    drawBone();
    WindArrow(&cam);

    SetLight();

    renderGround();
    renderSun(sunAngle);
    renderTrees();

    renderFences();
    renderTargets(targetWithLegs);
    renderHouses();

    ShowMenu();
    MoveSun();

    glutSwapBuffers();
}

void Reshape(int w, int h) {
    if(h == 0)
        h = 1;

    winx = w;
    winy = h;

    wr = (GLfloat) w / h;

    //Change to Projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h); /* set the viewport */
    SetPerspective(); /* set the camera perspective */

    glMatrixMode(GL_MODELVIEW);
}

void KeyDown(unsigned char key, int x, int y) {
    switch(key){
        case 'q': exit(0); break;
        case 'm': menu = (menu) ? GL_FALSE : GL_TRUE;
        default: break;
    }

    MoveCamKeyDown(&key);
}

void KeyUp(unsigned char key, int x, int y) {
    MoveCamKeyUp(&key);
}

void Mouse(int x, int y) {
    LookCam(&x, &y, &winx, &winy, &cam);
}

void GetDeltaTime(int * dt, int * old_t)
{
    *dt = glutGet(GLUT_ELAPSED_TIME) - *old_t;
    *old_t += *dt;
}

void Clock(int t) {
    GetDeltaTime(&dt, &t);
    MoveCam(&cam, &dt);
    glutPostRedisplay();
    glutTimerFunc(1000/fps, Clock, t);
}
