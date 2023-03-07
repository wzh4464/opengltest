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
// draw a rectangle with color (r,g,b)
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

void setAndRotate()
// set the modelview matrix and rotate it
{
    // clear the screen
    glClear(GL_COLOR_BUFFER_BIT);
    // set the color
    // glColor3f(0.0, 0.0, 0.0);

    // float m[16];

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 10, 50, 0, 10, 0, 0, 1, 0);

    glMultMatrixf(gsrc_getmo()); // get the rotation matrix from the rotation user-interface

    // show the modelview matrix in std output
    // glGetFloatv(GL_MODELVIEW_MATRIX, m);
    // printf("modelview matrix: *** \n");
    // printf("modelview matrix: %f %f %f %f \n", m[0], m[1], m[2], m[3]);
    // printf("modelview matrix: %f %f %f %f \n", m[4], m[5], m[6], m[7]);
    // printf("modelview matrix: %f %f %f %f \n", m[8], m[9], m[10], m[11]);
    // printf("modelview matrix: %f %f %f %f \n", m[12], m[13], m[14], m[15]);
}

// Drawing routine.
void drawScene(void)
// draw the scene
{
    setAndRotate();

    // save the current matrix
    glPushMatrix();

    // draw the object
    object(1.0, 0, 0);
    glTranslatef(-4, 20, 0);
    glRotatef(45, 0, 0, 1);
    glScalef(0.5, 0.5, 1.0);
    object(0, 1.0, 0);
    // translate to (0,20,0)
    glTranslatef(0.0, 20.0, 0.0);
    // rotate 45 degree around the z-axis
    glRotatef(45, 0, 0, 1);
    // draw the object
    object(0, 0, 1.0);

    // restore the current matrix
    glPopMatrix();
}

// Initialization routine.
void setup(void)
// set up the scene
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport); // viewport is by default the display window

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)viewport[2] / (float)viewport[3], 1, 100);

    // show the projection matrix in std output
    // float m[16];
    // glGetFloatv(GL_PROJECTION_MATRIX, m);
    // printf("projection matrix: %f %f %f %f \n", m[0], m[1], m[2], m[3]);
    // printf("projection matrix: %f %f %f %f \n", m[4], m[5], m[6], m[7]);
    // printf("projection matrix: %f %f %f %f \n", m[8], m[9], m[10], m[11]);
    // printf("projection matrix: %f %f %f %f \n", m[12], m[13], m[14], m[15]);
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
    
    // glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutMouseFunc(gsrc_mousebutton);
    glutMotionFunc(gsrc_mousemove);
    glutDisplayFunc(drawScene);
    // initialize the GLEW library
    glewExperimental = GL_TRUE;
    glewInit();

    // set the background color
    setup();

    // enter the main loop
    glutMainLoop();
}
