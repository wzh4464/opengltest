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

void show_coordinate();
void printMatrix(GLfloat *M, bool *printed);

bool M_printed = false;

void Part_1()
{
    glPushMatrix();
    glBegin(GL_POLYGON);
    // glColor4f(0.0, 1.0, 0.0, 0.5);
    glVertex3f(-2, 0, 0);
    glVertex3f(2, 0, 0);
    glVertex3f(2, 10, 0);
    glVertex3f(-2, 10, 0);
    glEnd();
    glPopMatrix();
}

void Part_2()
{
    // scale 0.5 on x and y
    glScalef(0.5, 0.5, 1);
    // Part 1
    Part_1();
}

// Drawing routine.

void object(void)
//
{
    // calculate some matrices

    // M1 = T(0, 5, 0) * R_z(45): blue
    // M2 = R_z(45) * T(0, 10, 0): green

    // load the identity matrix
    glPushMatrix();
    // glLoadIdentity();

    // red for original object
    glColor4f(1, 0, 0, 0.5);
    Part_1();

    // push
    glPushMatrix();
    // transform 1
    glTranslatef(0, 5, 0);
    glRotatef(45, 0, 0, 1);

    // print the matrix
    glColor4f(0, 0, 1, 0.5); // blue
    Part_1();
    // printMatrix("M1");

    // pop
    glPopMatrix();

    // push
    glPushMatrix();

    // transform
    glRotatef(45, 0, 0, 1);
    glTranslatef(0, 5, 0);

    // print the matrix
    glColor4f(0, 1, 0, 0.5); // green
    Part_1();

    // printMatrix("M2");
    
    // pop*2
    glPopMatrix();
    glPopMatrix();

}

void assignment_2_2()
{
    glPushMatrix();
    // green Part_2
    glColor4f(0, 1, 0, 0.5);

    // go to position 2
    // T(-2, 4, 0)
    glTranslatef(-2, 10, 0);
    // R_z(45)
    glRotatef(45, 0, 0, 1);
    // red Part_1
    glColor4f(1, 0, 0, 0.5);
    // scale
    glScalef(0.5, 0.5, 1);
    Part_1();
    // go to postion 3
    glPushMatrix();
    // M = T(0, 10, 0) * R_z(45)

    GLfloat M[16];

    glLoadIdentity();

    // Multiply T(0, 10, 0) * R_z(45) to M
    glTranslatef(0, 10, 0);
    glRotatef(45, 0, 0, 1);
    glGetFloatv(GL_MODELVIEW_MATRIX, M);

    glPopMatrix();



    printMatrix(M, &M_printed);

    // Multiply M to the current matrix
    glMultMatrixf(M);

    // blue Part_2
    glColor4f(0, 0, 1, 0.5);
    Part_1();
    glPopMatrix();


    glPopMatrix();
}

// Drawing routine.
void drawScene(void)
// draw the scene
{
    setAndRotate();

    // translate 100, 0, 100
    // glTranslatef(100, 0, 100);
    show_coordinate();

    glPushMatrix();
    // red, alpha 0.5
    assignment_2_2();
    glPopMatrix();

    // double buffer
    glColor3f(1, 0, 0);
    glutPostRedisplay();
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
    glutInitWindowSize(1500, 1500);
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

void show_coordinate()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    // use gray to draw the mesh of the coordinate
    glColor3f(0.5, 0.5, 0.5);

    for (int i = -15; i < 15; i++)
    {
        glBegin(GL_LINES);
        glVertex3f(-100, i, 0);
        glVertex3f(100, i, 0);
        glVertex3f(i, -100, 0);
        glVertex3f(i, 100, 0);
    }

    // draw the coordinate
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(-100, 0, 0);
    glVertex3f(100, 0, 0);
    glVertex3f(0, -100, 0);
    glVertex3f(0, 100, 0);
    glEnd();

    // draw the text around the origin
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos3f(0, 0, 1);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'z');
    glRasterPos3f(1, 0, 0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'x');
    glRasterPos3f(0, 1, 0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'y');

    glPopMatrix();
}

void printMatrix(GLfloat *M, bool *printed)
{
    if (*printed)
    {
        return;
    }
    printf("Matrix: \n");
    // M is column major, display it row major
    for (int i = 0; i < 4; i++)
    {
        printf("%f %f %f %f\n", M[i], M[i + 4], M[i + 8], M[i + 12]);
    }
    printf("\n");
    *printed = true;
}
