#include <stdio.h>
#include <freeglut.h>
#include "WorldView.h"

//------------------------------------------------------------------------

#define WIN_WIDTH 1020 // set the window width here
#define WIN_HEIGHT 768 // set the window height here
#define START_DELAY 1000 // delays the start of the animation by msecs

//------------------------------------------------------------------------

int main(int argc, char **argv) {
        /// setup window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)/2) - (WIN_WIDTH/2),
                           (glutGet(GLUT_SCREEN_HEIGHT)/2) - (WIN_HEIGHT/2));
    glutCreateWindow("Quiver");

        /// register callbacks
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);

        /// keyboard input
    glutIgnoreKeyRepeat(1);     // disables autofire
    glutKeyboardFunc(KeyDown);
    glutKeyboardUpFunc(KeyUp);

        /// mouse input
    glutWarpPointer(WIN_WIDTH/2, WIN_HEIGHT/2); // move mouse to center of viewport
    glutPassiveMotionFunc(Mouse);

        /// initialize default values
    InitDefaults();

        /// start the program clock
    glutTimerFunc(START_DELAY, Clock, START_DELAY);

        /// start GLUT main loop
    glutMainLoop();

    return 0;
}

