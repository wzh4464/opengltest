///////////////////////////////////
// OpenGL program to draw a square.
//
// Zihan
///////////////////////////////////

#include <GL/glew.h>
#include <GLUT/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "gsrc.h"

// Drawing routine.

void object(float r, float g, float b)
{

    // set the color
    glColor3f(r, g, b);
    // push the current matrix
    glPushMatrix();
    // translate to (-4,0,0)
    glTranslatef(-4.0, 0.0, 0.0);

    // draw a rectangle with size 20*8
    glBegin(GL_QUADS);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(8.0, 0.0, 0.0);
    glVertex3f(8.0, 20.0, 0.0);
    glVertex3f(0.0, 20.0, 0.0);
    glEnd();

    // pop the current matrix
    glPopMatrix();
    // flush the buffer
    glFlush();
}

// Drawing routine.
void drawScene(void)
{
    // draw the object
    object(1.0, 0, 0);
    glTranslatef(-4, 20, 0);
    glRotatef(45, 0, 0, 1);
    glScalef(0.5, 0.5, 1.0);
    object(0, 1.0, 0);
    // translate to (0,10,0)
    glTranslatef(0.0, 10.0, 0.0);
    // rotate 45 degree around the z-axis
    glRotatef(45, 0, 0, 1);
    // draw the object
    object(0, 0, 1.0);
}

// Initialization routine.
void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50, 50, -50, 50, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // show the size of the drawing area at right bottom corner
    char str[100];
    sprintf(str, "Window size: %d x %d", w, h);
    glutSetWindowTitle(str);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

// Main routine.
int main(int argc, char **argv)
{
    // initialize the GLUT library
    glutInit(&argc, argv);

    // glutInitContextVersion(4, 3);
    // glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    // initialize the display mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

    // set the window size
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    // create the window
    glutCreateWindow("main.cpp");
    glClear(GL_COLOR_BUFFER_BIT);

    // set the callback functions
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutMouseFunc(gsrc_mousebutton);
    glutMotionFunc(gsrc_mousemove);

    // initialize the GLEW library
    glewExperimental = GL_TRUE;
    glewInit();

    // set the background color
    setup();

    // enter the main loop
    glutMainLoop();
}
