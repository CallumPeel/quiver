#include "WorldView.h"
#include "CAMERA.h"
#include "PHYSICS.h"
#include "OFF.h"
#include "SCENE.h"

//------------------------------------------------------------------------

int fps = 80; // frame rate
int dt; // delta time
int winx; // viewport width
int winy; // viewport height

int thrown = 0;
GLboolean menu = GL_FALSE;
float angle = 90.0f;

Camera Cam;

Off* offList; // array of models (OFF): 1 = arrow, 2 = bone
Arrow arrow;
Static bone;
ListAABB listaabb;

Plane Ground = {(Vec3){0, 1.0, 0}, -1.0f};

//------------------------------------------------------------------------

void GetDeltaTime(int * dt, int * old_t);
void SetLight(void);
void WindArrow(Camera const * Cam);
void ActivateArrow();
void InitModel();
void InitStatic();

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
    InitStatic();
}

void InitModel()
{
    InitObject(&arrow.obj, (Vec3){0.5, 0.5, 0.5}, 0.5f);
    arrow.off = &offList[0];
    arrow.offset = (Vec3){0, 0, 0.50};
}

void InitStatic()
{
    listaabb.size = 1;
    listaabb.arr = malloc(sizeof(AABB) * 1);

    listaabb.arr[0].position = (Vec3){0, 0, -10.0};
    listaabb.arr[0].size = GetOffAABBSize(&offList[1]);

    bone.aabb = &listaabb.arr[0];
    bone.off = &offList[1];
    bone.scale = 1.0f;
    listaabb.arr[0].size = Mul(&listaabb.arr[0].size, bone.scale);
}

void Display(void) {
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //SetLight();
    LookAt(&Cam);
    WindArrow(&Cam);
    DrawScene();

    if(thrown)
        DrawArrow(&arrow);

    DrawStatic(&bone, (Vec3){1.0, 1.0, 0});
    DrawSizeBox(&bone.aabb->size);

    glutSwapBuffers();
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
        case 'q': exit(0); break;
        case ' ': ActivateArrow(); break;
        default: break;
    }

    MoveCamKeyDown(&key);
}

void KeyUp(unsigned char key, int x, int y) {
    MoveCamKeyUp(&key);
}

void Mouse(int x, int y) {
    if(!menu)   // do not orient camera or capture mouse while menu is open
        LookCam(&x, &y, &winx, &winy, &Cam);
}

void Clock(int t) {
    GetDeltaTime(&dt, &t);

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
    if(!menu) { // do not render if menu is open
        glPushMatrix();
            glTranslatef(Cam->Pos.x, Cam->Pos.y, Cam->Pos.z);   // align with cam pos
            glRotatef(-Cam->yaw, 0, 1.0, 0);                    // align with cam -yaw
            glRotatef(Cam->pitch, 1.0, 0, 0);                   // align with cam pitch
            glScalef(0.01, 0.01, 0.01);                         // scale arrow
            glTranslatef(-2.2f, 1.5f, -6.0);                    // position on screen
            glRotatef(Cam->yaw+angle, 0, 1.0, 0);               // rotate arrow
            drawWindArrow();                                    // draw model
        glPopMatrix();
    }
}

void ActivateArrow()
{
    thrown = 1;
    Vec3 pos = Add(&Cam.Pos, &Cam.Front);
    ShootArrow(&arrow.obj, &pos, &Cam.Front, 450.0);
}
