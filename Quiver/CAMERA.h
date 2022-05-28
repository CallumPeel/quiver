/// FILE:   CAMERA.H
/// TITLE:  GLUT Camera API
/// AUTHOR: Lane O'Rafferty
/// DATE:   May 2022
///-----------------------------------------------------------------------

#ifndef CAMERA_H
#define CAMERA_H

//------------------------------------------------------------------------

#include <freeglut.h>
#include "VECTORS.h"

//------------------------------------------------------------------------
    // should be replaced with a config file but meh

#define CAM_FORWARD         'w' // Move cam pos forward
#define CAM_BACK            's' // Move cam pos backward
#define CAM_CROSS_LEFT      'a' // Move cam pos to the left
#define CAM_CROSS_RIGHT     'd' // Move cam pos to the right

//------------------------------------------------------------------------

    /// @struct     GLUT camera object
    /// @brief      Defines the attributes of a Camera

typedef struct Camera{
    Vec3 Pos;       // camera position
    Vec3 Front;     // camera look at direction
    Vec3 Up;        // camera orientation
    float yaw;      // camera yaw
    float pitch;    // camera pitch
} Camera;

//------------------------------------------------------------------------

    /// @brief      allows use of Camera with gluLookAt
    /// @pre        Camera has been initialized
    /// @post       gluLookAt is called using Camera properties
    /// @param      cam: the Camera object
    /// @return     void

void LookAt(Camera * cam);

    /// @brief      Processes keystrokes when pressed
    /// @pre        A key is pressed
    /// @post       Keys are processed
    /// @param      key: pointer to a const char
    /// @return     void

void MoveCamKeyDown(unsigned char const * key);

    /// @brief      Processes keystrokes when released
    /// @pre        A key is released
    /// @post       Keys are processed
    /// @param      key: pointer to a const char
    /// @return     void

void MoveCamKeyUp(unsigned char const * key);

    /// @brief      Updates Camera's (x,z) position
    /// @pre        Camera has been initialized
    /// @post       Camera's position is updated
    /// @param      cam: pointer to a Camera object
    /// @param      dt: pointer to a const int (the delta time value)
    /// @return     void

void MoveCam(Camera * cam, int const * dt);

    /// @brief      Updates Camera's Front, pitch and yaw
    /// @pre        Camera has been initialized, winx and winy are not zero
    /// @post       Camera's front, pitch and yaw are updated
    /// @param      x: pointer's x coordinate
    /// @param      y: pointer's y coordinate
    /// @param      winx: the viewport window's length
    /// @param      winy: the viewport window's height
    /// @param      cam: pointer to a Camera object
    /// @return     void

void LookCam(int const * x, int const * y, int const * winx, int const * winy,
             Camera * cam);

void InitCam(Camera* C, const Vec3* pos, const Vec3* front, const Vec3* up);

void SetCamLookSpeed(float speed);

void SetCamMoveSpeed(float speed);

//------------------------------------------------------------------------

#endif // CAMERA_H
