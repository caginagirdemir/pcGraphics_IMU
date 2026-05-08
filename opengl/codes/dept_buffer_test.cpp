#include <iostream>

#include <GL/freeglut.h>


static float AngleX = 0.0;
static float AngleY = 0.0;
static float AngleZ = 0.0;
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
glEnable(GL_DEPTH_TEST);  

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
	glRotatef(AngleZ, 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin( GL_QUADS );
    glColor3f(   1.0f,  0.0f, 0.0f ); 
    glVertex3f(  1.0f,  1.0f, 0.0f ); 
    glColor3f(   0.0f,  1.0f, 0.0f );
    glVertex3f( -1.0f,  1.0f, 0.0f ); 
    glColor3f(   0.0f,  0.0f, 1.0f );
    glVertex3f( -1.0f, -1.0f, 0.0f );
   	glColor3f(   1.0f,  0.0f, 0.0f );
    glVertex3f(  1.0f, -1.0f, 0.0f );
    glEnd();
    
    glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
	glRotatef(AngleY, 0.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin( GL_QUADS );
    glColor3f(   1.0f,  0.0f, 0.0f ); 
    glVertex3f(  1.0f,  1.0f, 0.0f ); 
    glColor3f(   0.0f,  1.0f, 0.0f );
    glVertex3f( -1.0f,  1.0f, 0.0f );
    glColor3f(   0.0f,  0.0f, 1.0f );
    glVertex3f( -1.0f, -1.0f, 0.0f ); 
   	glColor3f(   1.0f,  0.0f, 0.0f );
    glVertex3f(  1.0f, -1.0f, 0.0f ); 
    glEnd();
	

	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
	glRotatef(AngleX, 1.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin( GL_QUADS );
    glColor3f(   1.0f,  0.0f, 0.0f );
    glVertex3f(  1.0f,  1.0f, 0.0f );
    glColor3f(   0.0f,  1.0f, 0.0f );
    glVertex3f( -1.0f,  1.0f, 0.0f );
    glColor3f(   0.0f,  0.0f, 1.0f );
    glVertex3f( -1.0f, -1.0f, 0.0f );
   	glColor3f(   1.0f,  0.0f, 0.0f );
    glVertex3f(  1.0f, -1.0f, 0.0f );
    glEnd();
	
	glutSwapBuffers();
}


void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}


void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
}


void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x':
		AngleX += 10.0;
		glutPostRedisplay();
		break;
	case 'y':
		AngleY += 10.0;
		glutPostRedisplay();
		break;
	case 'z':
		AngleZ += 10.0;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("main7.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glutMainLoop();
}
