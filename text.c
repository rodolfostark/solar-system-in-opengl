#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

GLuint tex;
GLUquadric *sphere;



void FreeCreatedTexture(GLuint texture)
{
    glDeleteTextures(1, &texture);
}

void make_tex(void)
{
    unsigned char data[256][256][3];
    FILE *file;

    // open texture data
    file = fopen("2k_sun.jpg", "r");
    if (file == NULL)
        return 0;
    fread(data, 256 * 256 * 3, 1, file);
    fclose(file);

    
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, (const GLvoid *)data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


void draw(void)
{
    glClearColor(0.5, 0.5, 1.0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -2.0);
    glRotatef(45, 0, 1, 0);

    glColor3f(1.0, 1.0, 1.0);
    gluQuadricDrawStyle(sphere, GLU_FILL);
    glBindTexture(GL_TEXTURE_2D, tex);
    gluQuadricTexture(sphere, GL_TRUE);
    gluSphere(sphere, 1.0, 32, 16);

    glutSwapBuffers();
}

void resize(int w, int h)
{
    if (!h)
        h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, 1.0 * w / h, 0.1, 100.0);
}

void init(void)
{
    glEnable(GL_DEPTH_TEST);
    make_tex();
    sphere = gluNewQuadric();
    glEnable(GL_TEXTURE_2D);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 512);

    glutCreateWindow("Test");

    glutDisplayFunc(draw);
    glutReshapeFunc(resize);

    init();

    glutMainLoop();
}