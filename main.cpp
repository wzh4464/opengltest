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
    // glColor3f(1.0, 1.0, 1.0);

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

void Part(float r, float h)
{
    // Draw a cylinder with radius r and height h
    GLUquadricObj *quad = gluNewQuadric();
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, r, r, h, 32, 1);
    gluDeleteQuadric(quad);
    glFlush();
    glPopMatrix();
    glFlush();
}

// Drawing routine.
void drawScene(void)
// draw the scene
{
    setAndRotate();

    // save the current matrix
    glPushMatrix();

    // draw the object
    // glClear(GL_COLOR_BUFFER_BIT);

    Part(4, 20); // Part 1
    glScalef(0.5, 0.5, 1);
    glRotatef(45, 0, 0, 1);
    glTranslatef(-4, 20, 0);
    Part(4, 20); // Part 2
    glRotatef(45, 0, 0, 1);
    glTranslatef(0, 20, 0);
    Part(4, 20); // Part 3
    glColor3f(1, 0, 0);
    glFlush();

    glPopMatrix();
    glColor3f(1, 0, 0);
    glutSwapBuffers();
    // draw a coordinate system
    // glPushMatrix();
    // glTranslatef(0, 0, 0);
    // glScalef(0.5, 0.5, 0.5);
    // gsrc_drawaxes();
    // glPopMatrix();
    // glFlush();
}

// Initialization routine.
void setup(void)
// set up the scene
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport); // viewport is by default the display window

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)viewport[2] / (float)viewport[3], 1, 100);
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
    // initialize the GLEW library

    // glutInitContextVersion(4, 3);
    // glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    // initialize the display mode
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    // set the window size
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    // create the window
    glutCreateWindow("main.cpp");
    // set the background color
    setup();

    // set the callback functions

    // glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutMouseFunc(gsrc_mousebutton);
    glutMotionFunc(gsrc_mousemove);
    glutDisplayFunc(drawScene);

    glewExperimental = GL_TRUE;
    glewInit();

    // first frame
    drawScene();

    // enter the main loop
    glutMainLoop();
}
