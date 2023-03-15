#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <GL/glew.h>
#include <GLUT/glut.h>

#define PI 3.14159265358979323846f

// camera offset
// it is controlled by w,a,s,d
int xoffset = 0;
int yoffset = 0;

// zoom parameter
// it is controlled by = and -
float zoom = 1.0;

float v0[3], v1[3];
// v0 and v1 are used to calculate the rotation angle
// v0 is the previous mouse position
// v1 is the current mouse position

float mo[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

float clamp(float x, float a, float b);
float dot(const float *a, const float *b);
float norm(const float *a);
void vassign(float *a, float x, float y, float z);
void vassign(float *a, const float *b);
bool vequal(float *a, float *b);
void cross(float *a, const float *b, const float *c);
void normalize(float *a);

float *gsrc_getmo() { return mo; }

void gsrc_mousebutton(int button, int state, int x, int y)
{

  // print to error output
  // fprintf(stderr, "button: %d, state: %d, x: %d, y: %d \r", button, state, x, y);

  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    vassign(v0, -2.0 * y / glutGet(GLUT_WINDOW_HEIGHT) + 1, 1, 2.0 * x / glutGet(GLUT_WINDOW_WIDTH) - 1);
    normalize(v0);
  }
  // else if (button == 3)
  // { // 滚轮向上滚
  //   glScalef(1.1, 1.1, 1.1);
  //   glutPostRedisplay();
  // }
  // else if (button == 4)
  // { // 滚轮向下滚
  //   glScalef(0.9, 0.9, 0.9);
  //   glutPostRedisplay();
  // }
}

void gsrc_mousemove(int x, int y)
{
  float axis[3], angle;

  vassign(v1, -2.0 * y / glutGet(GLUT_WINDOW_HEIGHT) + 1, 1, 2.0 * x / glutGet(GLUT_WINDOW_WIDTH) - 1);
  normalize(v1);
  if (vequal(v0, v1))
    return;
  cross(axis, v0, v1);
  normalize(axis);
  angle = acosf(clamp(dot(v0, v1), -1, 1));
  vassign(v0, v1);

  glPushMatrix();
  glLoadIdentity();
  glRotatef(angle * 180 / PI, axis[0], axis[1], axis[2]);
  glMultMatrixf(mo);
  glGetFloatv(GL_MODELVIEW_MATRIX, mo);
  glPopMatrix();
  glutPostRedisplay();
}

void gsrc_move(int x, int y)
// move the camera
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  xoffset += x;
  yoffset += y;
  // gluLookAt(-10 + xoffset, 10 + yoffset, 50, -10 + xoffset, 10 + yoffset, 0, 0, 1, 0);
  glutPostRedisplay();
}

// Keyboard input processing routine.
void gsrc_keyInput(unsigned char key, int, int)
{

  // show key code in error output
  fprintf(stderr, "key code: %d \n", key);

  switch (key)
  {
  // esc key
  case 27:
    exit(0);
    break;

  // arrow keys
  // up w
  case 119:
    gsrc_move(0, 1);
    break;
  // down s
  case 115:
    gsrc_move(0, -1);
    break;
  // left a
  case 97:
    gsrc_move(-1, 0);
    break;
  // right d
  case 100:
    gsrc_move(1, 0);
    break;

  // zoom in/out
  // +
  case 61:
    zoom *= 1.1;
    glutPostRedisplay();
    break;
  // -
  case 45:
    zoom *= 0.9;
    glutPostRedisplay();
    break;

  // r reset
  case 114:
    xoffset = 0;
    yoffset = 0;
    zoom = 1.0;
    // mo = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
      {
        mo[i * 4 + j] = (i == j) ? 1 : 0;
      }
    }
    glutPostRedisplay();
    break;

  default:
    break;
  }
  // show zoom to window title
  char title[100];
  sprintf(title, "zoom: %f", zoom);
  glutSetWindowTitle(title);
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
  // gluLookAt(-10, 10, 50, -10, 10, 0, 0, 1, 0);
  // gluLookAt(-10 + xoffset, 10 + yoffset, 50, -10 + xoffset, 10 + yoffset, 0, 0, 1, 0);
  gluLookAt(xoffset, 50 / zoom, yoffset, xoffset, 0, yoffset, 1, 0, 0);

  glMultMatrixf(gsrc_getmo()); // get the rotation matrix from the rotation user-interface
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
  gluPerspective(45, (float)viewport[2] / (float)viewport[3], 0.1, 100);
  // gluPerspective(45, (float)viewport[2] / (float)viewport[3], 0.1 / zoom, 100 / zoom);
}

float clamp(float x, float a, float b) { return x < a ? a : (x < b ? x : b); }
float dot(const float *a, const float *b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; }
float norm(const float *a) { return sqrtf(dot(a, a)); }
void vassign(float *a, float x, float y, float z)
{
  a[0] = x;
  a[1] = y;
  a[2] = z;
}
void vassign(float *a, const float *b)
{
  a[0] = b[0];
  a[1] = b[1];
  a[2] = b[2];
}
bool vequal(float *a, float *b) { return memcmp(a, b, 3 * sizeof(float)) == 0; }
void cross(float *a, const float *b, const float *c)
{
  a[0] = b[1] * c[2] - c[1] * b[2];
  a[1] = -b[0] * c[2] + c[0] * b[2];
  a[2] = b[0] * c[1] - c[0] * b[1];
}
void normalize(float *a)
{
  float l = norm(a);
  a[0] /= l;
  a[1] /= l;
  a[2] /= l;
}
