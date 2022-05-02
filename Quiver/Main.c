#include <stdio.h>
#include <GL/freeglut.h>
#include "WorldView.h"

// window size
int wWidth = 950, wHeight = 700;

int main(int argc, char **argv) {
    // setup window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(wWidth, wHeight);
    glutInitWindowPosition(500, 50);
    glutCreateWindow("Quiver");

    // register callbacks
    glutDisplayFunc(display);
    //glutIdleFunc(display);
    glutReshapeFunc(reShape);
    glutTimerFunc(1000, timer, 0);

    // keyboard input
    glutKeyboardFunc(onKeyPress);
    glutKeyboardUpFunc(onKeyRelease);
    glutIgnoreKeyRepeat(1);

    // mouse input
    glutPassiveMotionFunc(mouseMove);
    glutWarpPointer(wWidth/2, wHeight/2);
    glutSetCursor(GLUT_CURSOR_NONE);

    myInit(wWidth, wHeight);

    glutMainLoop();

    return 0;
}

