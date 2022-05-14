#include "CAMERA.h"
#include "MATH_EXT.h"

//------------------------------------------------------------------------

GLboolean forward = GL_FALSE;
GLboolean backward = GL_FALSE;
GLboolean cross_left = GL_FALSE;
GLboolean cross_right = GL_FALSE;

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

    pos->x += c.x * CamMoveSpeed * (*dt);
    pos->z += c.z * CamMoveSpeed * (*dt);
}

void MoveCam(Camera * cam, int const * dt) {
    if (forward) {
        cam->Pos.x += cam->Front.x * CamMoveSpeed * (*dt);
        cam->Pos.z += cam->Front.z * CamMoveSpeed * (*dt);
    }
    if (backward) {
        cam->Pos.x -= cam->Front.x * CamMoveSpeed * (*dt);
        cam->Pos.z -= cam->Front.z * CamMoveSpeed * (*dt);
    }
    if (cross_left) {
        Strafe(&cam->Pos, &cam->Up, &cam->Front, dt);
    }
    if (cross_right) {
        Strafe(&cam->Pos, &cam->Front, &cam->Up, dt);
    }
}

#define OFFSET_X ((float)*x - *winx/2.0f) * CamLookSpeed
#define OFFSET_Y ((float)*y - *winy/2.0f) * CamLookSpeed

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
