#include "WorldView.h"
#include "CAMERA.h"
#include "PHYSICS.h"
#include "OFF.h"
#include "SCENE.h"
#include "ImageProcessor.h"
#include <time.h>

//------------------------------------------------------------------------

Image img;
int quit = 0;
int a = 0;

//------------------------------------------------------------------------

int fps = 80; // frame rate
int dt; // delta time
int windDT = 0;
int winx; // viewport width
int winy; // viewport height

int thrown = 0;
float windAngle = 0.0f;

Camera Cam;

Off* offList; // array of models (OFF): 1 = arrow, 2 = bone
Arrow arrow;
Static tgt1, tgt2, tgt3;
ListAABB listaabb;

Plane Ground = {(Vec3){0, 1.0, 0}, -1.0f};

//------------------------------------------------------------------------

void GetDeltaTime(int * dt, int * old_t);
void SetLight(void);
void WindArrow(Camera const * Cam);
void ActivateArrow();
void InitModel();
void InitStatic();
void ChangeWind();

//------------------------------------------------------------------------

void Init() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glutSetCursor(GLUT_CURSOR_NONE);

    glClearColor(0, 0.5, 1, 1.0f);
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(1.0);

    InitCam(&Cam, 0, 0, 0);

    LoadOff(&offList, "OffList.txt");
    InitModel();

    loadImage(&img, "test.png");

    srand(time(NULL));
}

void InitModel()
{
    InitObject(&arrow.obj, (Vec3){0.5, 0.5, 0.5}, 0.5f);
    arrow.off = &offList[0];
    arrow.offset = (Vec3){0, 0, 0.8f};
}

void InitStatic()
{
    Off* model;
    listaabb.size = 1;
    listaabb.arr = malloc(sizeof(AABB) * listaabb.size);

    model = &offList[1];
    listaabb.arr[0].position = (Vec3){0, 0, -10.0};
    listaabb.arr[0].size = GetOffAABBSize(model);

    tgt1.aabb = &listaabb.arr[0];
    tgt1.off = model;
    tgt1.scale = 1.0f;
    listaabb.arr[0].size = Mul(&listaabb.arr[0].size, tgt1.scale);
}

void ChangeWind()
{
    windDT += dt;
    windDT %= 1000;
    if (windDT == 0) windAngle = rand() % 360;
    windAngle += dt/100.0;

    if (!windDT) windAngle = rand() % 360;

    Vec3 dir;
    float angle = windAngle * 3.14159 / 180.0;
    dir.x = -sin(angle) * 16;
    dir.y = -9.81f;
    dir.z = -cos(angle) * 16;

    SetPassiveForce(&dir);
}

void Display(void) {

    if(quit == 0) {

        glMatrixMode(GL_MODELVIEW);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        //SetLight();
        LookAt(&Cam);
        WindArrow(&Cam);
        DrawScene();

        if(thrown)
            DrawArrow(&arrow);
        glutSwapBuffers();

    } else {
        displayImage(&img);
        if(a == 0) {
            glutSwapBuffers();
            a++;
        }
    }
}

void Reshape(int w, int h) {
    winx = w;
    winy = h;

    if (!h) h = 1;
    double ratio = w * 1.0f / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0, ratio, 0.01, 100);
}

void KeyDown(unsigned char key, int x, int y) {
    switch(key){
        case 'q':
            quit++;
            if(quit == 2) exit(0);
            break;
        case ' ': ActivateArrow(); break;
        default: break;
    }

    MoveCamKeyDown(&key);
}

void KeyUp(unsigned char key, int x, int y) {
    MoveCamKeyUp(&key);
}

void Mouse(int x, int y) {
    LookCam(&x, &y, &winx, &winy, &Cam);
}

void Clock(int t) {
    GetDeltaTime(&dt, &t);
    ChangeWind();

    MoveCam(&Cam, &dt);
    AddSunAngle(10.0f * dt / 1000);
    UpdatePhysics(&arrow.obj, &Ground, &listaabb, dt);

    glutPostRedisplay();
    glutTimerFunc(1000/fps, Clock, t);
}

void GetDeltaTime(int * dt, int * old_t) {
    *dt = glutGet(GLUT_ELAPSED_TIME) - *old_t;
    *old_t += *dt;
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

void WindArrow(Camera const * Cam) {
    glPushMatrix();
            glTranslatef(Cam->Pos.x, Cam->Pos.y, Cam->Pos.z);   // align with cam pos
            glRotatef(-Cam->yaw, 0, 1.0, 0);                    // align with cam -yaw
            glRotatef(Cam->pitch, 1.0, 0, 0);                   // align with cam pitch
            glScalef(0.01, 0.01, 0.01);                         // scale arrow
            glTranslatef(-2.2f, 1.5f, -6.0);                    // position on screen
            glRotatef(windAngle+180.0+Cam->yaw, 0, 1.0, 0);              // rotate arrow
            drawWindArrow();                                    // draw model
    glPopMatrix();
}

void ActivateArrow()
{
    thrown = 1;
    Vec3 pos = Add(&Cam.Pos, &Cam.Front);
    ShootArrow(&arrow.obj, &pos, &Cam.Front, 450.0);
}
