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
