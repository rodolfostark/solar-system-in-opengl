#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

static int year = 0, day = 0;

#define earth_size 0.1
#define earth_distance 3

GLuint* texture_earth;
GLuint* texture_sun;

void loadTexture(GLuint* tex, const char* filename){
// Carregando imagem de textura do Sol
  unsigned char data[640][480][3];
  FILE *file;
  // open texture data
  file = fopen(filename, "rb");
  if (file == NULL)
    return 0;
  fread(data, 640 * 480 * 3, 1, file);
  fclose(file);

  glGenTextures(1, &tex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, (const GLvoid *) data);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

float mercury_size = earth_size * 0.37, venus_size = earth_size * 0.94,
      moon_size = earth_size * 0.27, mars_size = earth_size * 0.532,
      jupiter_size = earth_size * 11.21, saturn_size = earth_size * 9.45,
      uranus_size = earth_size * 4.01, neptune_size = earth_size * 3.88,
      pluto_size = earth_size * 0.19;

float mercury_distance = earth_distance * 0.39,
      venus_distance = earth_distance * 0.72,
      mars_distance = earth_distance * 1.52,
      jupiter_distance = earth_distance * 5.2,
      saturn_distance = earth_distance * 9.54,
      uranus_distance = earth_distance * 19.2,
      neptune_distance = earth_distance * 30.06,
      pluto_distance = earth_distance * 40;

void init(void)
{
  glClearColor(0.38, 0.4, 0.53, 0.21);
  glShadeModel(GL_FLAT);
  glEnable(GL_TEXTURE_2D);\
  loadTexture(texture_earth, "2k_earth_daymap.jpg");
  loadTexture(texture_sun, "2k_sun.jpg");
}

void stars(void)
{
  int noOfStars = rand() % 10;
  int i = 0;

  while (i < noOfStars)
  {
    glColor3f(0.0, 1.0, 1.0);
    glPointSize(20.0f);

    int x = rand() % 10;
    int y = rand() % 10;
    int z = -8.0;

    glBegin(GL_POINTS);
    glVertex3f(x, y, z);
    glEnd();

    i++;
  }
  glFlush();
  glutSwapBuffers();
}
void make_texture(GLUquadricObj *planet, GLuint* tex)
{
  gluQuadricDrawStyle(planet, GLU_FILL);
  gluQuadricNormals(planet, GLU_SMOOTH);
  glBindTexture(GL_TEXTURE_2D, tex);
  gluQuadricTexture(planet, GL_TRUE);
}

void renderPlanet(GLUquadricObj *planet, float size, float translateX,
                  float translateY, float translateZ, float rotationAngle,
                  float rotationX, float rotationY, float rotationZ, float yearRateFromEarth, GLfloat red, GLfloat green, GLfloat blue)
{
  glPopMatrix();
  glColor3f(red, green, blue);
  glPushMatrix();
  glRotatef((GLfloat)year * yearRateFromEarth, 0.0, 1.0, 0.0);
  glTranslatef(translateX, translateY, translateZ);
  glRotatef((GLfloat)year * yearRateFromEarth * rotationAngle, rotationX, rotationY, rotationZ);
  gluSphere(planet, size, 200, 200);
}

void displayFirstSet(void)
{
  // stars();
  GLUquadricObj *sun = NULL;
  sun = gluNewQuadric();
  GLUquadricObj *mercury = NULL;
  mercury = gluNewQuadric();
  GLUquadricObj *venus = NULL;
  venus = gluNewQuadric();
  GLUquadricObj *earth = NULL;
  earth = gluNewQuadric();
  GLUquadricObj *moon = NULL;
  moon = gluNewQuadric();
  GLUquadricObj *mars = NULL;
  mars = gluNewQuadric();
  GLUquadricObj *jupiter = NULL;
  jupiter = gluNewQuadric();
  GLUquadricObj *saturn = NULL;
  saturn = gluNewQuadric();
  GLUquadricObj *uranus = NULL;
  uranus = gluNewQuadric();
  GLUquadricObj *neptune = NULL;
  neptune = gluNewQuadric();
  GLUquadricObj *pluto = NULL;
  pluto = gluNewQuadric();

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.98, 0.83, 0.25);
  glPushMatrix();

  gluSphere(sun, 1.0, 200, 160);           /* draw sun */
  glRotatef((GLfloat)year, 0.0, 1.0, 0.0); // rotate sun

  renderPlanet(mercury, mercury_size, mercury_distance, 1.0, 0.0, 2, 0.0, 1.0, 0.0, 4.0, 1.0, 0.2, 0.8);
  renderPlanet(venus, venus_size, venus_distance, 1.0, 0.0, 2, 0.0, 1.0, 0.0, 1.6, 1.0, 0.3, 0.4);
  renderPlanet(earth, earth_size, earth_distance, 1.0, 0.0, 2, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0); // **** Render Mars****
  glColor3f(1.0, 1.0, 1.0);
  glTranslatef(0.5, 0.0, 0.0);
  glRotatef((GLfloat) day * 2, 0.0, 1.0, 0.0);
  gluSphere(moon, moon_size, 100, 80);
  renderPlanet(mars, mars_size, mars_distance, 1.0, 0.0, 2, 0.0, 1.0, 0.0, 0.5, 1.0, 0.0, 0.0);
  renderPlanet(jupiter, jupiter_size, jupiter_distance, 1.0, 0.0, 2, 0.0, 1.0, 0.0, 0.08, 1.0, 0.6, 0.4);
  renderPlanet(saturn, saturn_size, saturn_distance, 1.0, 0.0, 2, 0.0, 1.0,
               0.0, 0.03, 0.92, 0.8, 0.6);
  renderPlanet(uranus, uranus_size, uranus_distance, 1.0, 0.0, 2, 0.0, 1.0,
               0.0, 0.01, 0.6, 0.73, 0.85);
  renderPlanet(neptune, neptune_size, neptune_distance, 1.0, 0.0, 2, 0.0, 1.0,
               0.0, 0.006, 0.25, 0.47, 0.85);
  renderPlanet(pluto, pluto_size, pluto_distance, 1.0, 0.0, 2, 0.0, 1.0, 0.0, 0.004, 0.8, 0.8, 0.8);
  glPopMatrix();
  glutSwapBuffers();
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(120.0, (GLfloat)w / (GLfloat)h, 2.0, 550.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(4.0, 4.0, 4.0, 0.0, 3.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 'd':
    day = (day + 10) % 360;
    glutPostRedisplay();
    break;
  case 'D':
    day = (day - 10) % 360;
    glutPostRedisplay();
    break;
  case 'y':
    year = (year + 5) % 360;
    glutPostRedisplay();
    break;
  case 'Y':
    year = (year - 5) % 360;
    glutPostRedisplay();
    break;
  default:
    break;
  }
}

void idle()
{
  glutPostRedisplay();
  day = (day + 10);
  year = (year + 5);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(1270, 720);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(displayFirstSet);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}
