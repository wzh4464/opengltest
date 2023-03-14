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

void Part_1()
{
    // rectangle 6 * 20
    glPushMatrix();
    // glRotatef(90, 0, 0, 1);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-3, 0, -10);
    glVertex3f(3, 0, -10);
    glVertex3f(3, 0, 10);
    glVertex3f(-3, 0, 10);
    glEnd();
    glPopMatrix();
}

void Part_2()
{
    // rectangle 6*10
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, 0, 3);
    glVertex3f(0, 0, -3);
    glVertex3f(10, 0, -3);
    glVertex3f(10, 0, 3);
    glEnd();
    glPopMatrix();
}

// Drawing routine.

// void object(void)
// //
// {
//     glPushMatrix();
//     // glTranslatef(3, 0, -10);
//     glRotatef(60, 0, 1, 0);
//     glRotatef(15, 1, 0, 0);
//     Part_2();
//     glPopMatrix();
// }

void object()
{
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();
    glPushMatrix();
    Part_1();
    glPushMatrix();
    glTranslatef(3, 0, -10);
    glRotatef(60, 0, 1, 0);
    Part_2();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-3, 0, -10);
    glRotatef(30, 0, 1, 0);
    glPushMatrix();
    glScalef(-1, 1, 1);
    Part_2();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}

// Drawing routine.
void drawScene(void)
// draw the scene
{
    setAndRotate();

    object();

    // double buffer
    glColor3f(1, 0, 0);
    glutSwapBuffers();
}

// Main routine.
int main(int argc, char **argv)
{
    // initialize the GLUT library
    glutInit(&argc, argv);

    // glutInitContextVersion(4, 3);
    // glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    // initialize the display mode
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // set the window size
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    // create the window
    glutCreateWindow("main.cpp");
    // glClear(GL_COLOR_BUFFER_BIT);

    // set the callback functions

    // glutReshapeFunc(resize);
    glutKeyboardFunc(gsrc_keyInput);
    glutMouseFunc(gsrc_mousebutton);
    glutMotionFunc(gsrc_mousemove);
    glutDisplayFunc(drawScene);
    // initialize the GLEW library
    glewExperimental = GL_TRUE;
    glewInit();

    // set the background color
    setup();

    // glutIdleFunc(drawScene);
    // draw the scene
    glutPostRedisplay();
    // drawScene();

    // enter the main loop
    glutMainLoop();
}
