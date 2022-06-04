#include <freeglut.h>
#include "WorldView.h"

//------------------------------------------------------------------------

const int WIN_WIDTH = 800; // viewport width
const int WIN_HEIGHT = 600; // viewport height
const unsigned DELAY = 500; // start delay (milliseconds)

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
    glutPassiveMotionFunc(Mouse);

        /// initialize default values
    Init();

        /// start the program clock
    glutTimerFunc(DELAY, Clock, DELAY);

        /// start GLUT main loop
    glutMainLoop();

    return 0;
}

