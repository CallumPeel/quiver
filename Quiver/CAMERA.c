#include "CAMERA.h"
#include "MATH_EXT.h"

//------------------------------------------------------------------------

GLboolean forward = GL_FALSE;
GLboolean backward = GL_FALSE;
GLboolean cross_left = GL_FALSE;
GLboolean cross_right = GL_FALSE;

//------------------------------------------------------------------------

float _lookspeed = 0.125;
float _movespeed = 0.0025;

//------------------------------------------------------------------------

void LookAt(Camera * cam)
{
    gluLookAt(
        cam->Pos.x,
        cam->Pos.y,
        cam->Pos.z,
        cam->Pos.x + cam->Front.x * cos(DTR(cam->pitch)),
        cam->Pos.y + cam->Front.y,
        cam->Pos.z + cam->Front.z * cos(DTR(cam->pitch)),
        cam->Up.x,
        cam->Up.y,
        cam->Up.z
    );
}

void MoveCamKeyDown(unsigned char const * key)
{
    switch(*key) {
        case CAM_FORWARD: forward = GL_TRUE; break;
        case CAM_BACK: backward = GL_TRUE; break;
        case CAM_CROSS_LEFT: cross_left = GL_TRUE; break;
        case CAM_CROSS_RIGHT: cross_right = GL_TRUE; break;

        default: break;
    }
}

void MoveCamKeyUp(unsigned char const * key)
{
    switch(*key) {
        case CAM_FORWARD: forward = GL_FALSE; break;
        case CAM_BACK: backward = GL_FALSE; break;
        case CAM_CROSS_LEFT: cross_left = GL_FALSE; break;
        case CAM_CROSS_RIGHT: cross_right = GL_FALSE; break;

        default: break;
    }
}

void Strafe(Vec3 * pos, Vec3 const * u, Vec3 const * v, int const * dt)
{
    Vec3 c = Cross(u, v);
    c = Normalize(&c);

    pos->x += c.x * _movespeed * (*dt);
    pos->z += c.z * _movespeed * (*dt);
}

void MoveCam(Camera * cam, int const * dt) {
    if (forward) {
        cam->Pos.x += cam->Front.x * _movespeed * (*dt);
        cam->Pos.z += cam->Front.z * _movespeed * (*dt);
    }
    if (backward) {
        cam->Pos.x -= cam->Front.x * _movespeed * (*dt);
        cam->Pos.z -= cam->Front.z * _movespeed * (*dt);
    }
    if (cross_left) {
        Strafe(&cam->Pos, &cam->Up, &cam->Front, dt);
    }
    if (cross_right) {
        Strafe(&cam->Pos, &cam->Front, &cam->Up, dt);
    }
}

#define OFFSET_X ((float)*x - *winx/2.0f) * _lookspeed
#define OFFSET_Y ((float)*y - *winy/2.0f) * _lookspeed

void LookCam(int const * x, int const * y, int const * winx, int const * winy,
             Camera * cam)
{
    cam->yaw = fmod(cam->yaw + OFFSET_X, 360.0);

    cam->pitch -= OFFSET_Y;
    if (cam->pitch > 89.9) cam->pitch = 89.9;
    if (cam->pitch < -89.9) cam->pitch = -89.9;

    cam->Front.x = sin(DTR(cam->yaw));
    cam->Front.y = sin(DTR(cam->pitch));
    cam->Front.z = -cos(DTR(cam->yaw));
    cam->Front = Normalize(&cam->Front);

    glutWarpPointer(*winx/2, *winy/2);
}

void InitCam(Camera* C, const Vec3* pos, const Vec3* front, const Vec3* up)
{
    if (pos == 0)
        C->Pos = (Vec3){0, 0, 0};
    else
        C->Pos = *pos;

    if (front == 0)
        C->Front = (Vec3){0, 0, -1.0};
    else
        C->Front = *front;

    if (up == 0)
        C->Up = (Vec3){0, 1.0, 0};
    else
        C->Up = *up;

    C->yaw = 0.0f;
    C->pitch = 0.0f;
}

void SetCamLookSpeed(float speed)
{
    _lookspeed = speed;
}

void SetCamMoveSpeed(float speed)
{
    _movespeed = speed;
}
