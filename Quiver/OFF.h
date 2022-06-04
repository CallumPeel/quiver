#ifndef OFF_V1_0_H_INCLUDED
#define OFF_V1_0_H_INCLUDED

#include "Vectors.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//---------------------------------------------------------------------------

    /// @brief      Stores and manipulates vertex and face data
    ///             for a 3D object that uses OFF notation.
    ///
    /// @author     Lane O'R
    /// @version    1.2
    /// @date       April 2022

//---------------------------------------------------------------------------

    /// @struct     Face
    /// @brief      Defines a 3D triangle face
typedef struct Face {
    unsigned a,
             b,
             c;
} Face;

    /// @struct     Off
    /// @brief      Holds the model data
typedef struct Off {
    unsigned nverts,
             nfaces;

    Vec3* verts;
    Face* faces;
} Off;

    /// @brief      reads OFF data from a file and stores it into
    ///             the object
    ///
    /// Only reads vertices and faces. Assumes all faces are
    /// triangles.
    ///
    /// @pre        Assumes file has been parsed for errors
    /// @param      off - a pointer to the Off object
    /// @param      filename - c-string containing the name of the file
    ///             being read.
    /// @return     void
void ReadOffFile(Off* off, const char* filename);

    /// @brief      deallocates mem from Off's verts and faces
    ///             sets the pointers to NULL
    /// @pre        assumes mem has been allocated to pointers
    /// @param      off - a pointer to the Off object
    /// @return     void
    /// @post       off data is deallocated and pointers are set
    ///             to NULL
void FreeOff(Off* off);

    /// @brief      prints out Off data held by an Off struct
    /// @pre        assumes Off data has been set
    /// @post       Off data is printed to the screen
    /// @param      off - a pointer to the Off object
    /// @return     void
void PrintOff(Off* off);

Vec3 GetOffCenter(const Off* off);

double GetOffBSR(const Off* off, const Vec3* c);

void NormOff(Off* off);

#endif // OFF_V1_0_H_INCLUDED
