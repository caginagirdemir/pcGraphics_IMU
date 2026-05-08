#include <gl/glut.h>
#include <math.h>
void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
}
void display(void) {

	glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,1.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLE_STRIP);
		 glVertex3f(120,180,0);
         glVertex3f(90,210,0);
         glVertex3f(180,180,0);
         glVertex3f(180,180,0);
         glVertex3f(90,210,0);
         glVertex3f(210,210,0);

		 glVertex3f(180,180,0);
         glVertex3f(180,120,0);
         glVertex3f(210,210,0);
         glVertex3f(210,210,0);
         glVertex3f(180,120,0);
         glVertex3f(210,90,0);


		 glVertex3f(210,90,0);
         glVertex3f(180,120,0);
         glVertex3f(120,120,0);
         glVertex3f(120,120,0);
         glVertex3f(90,90,0);
         glVertex3f(210,90,0);


		 glVertex3f(90,90,0);
         glVertex3f(120,120,0);
         glVertex3f(120,180,0);
         glVertex3f(120,180,0);
         glVertex3f(90,90,0);
         glVertex3f(90,210,0);

	glEnd();
	glFlush();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Open GL main.cpp");
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
