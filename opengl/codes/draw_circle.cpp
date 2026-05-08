#include <gl/glut.h>
#include <math.h>
void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
}
void display(void) {
    float t;
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_POLYGON);
    for (int i=0;i<360;i++)
    {
        t=i*3.142/180;
        glVertex2f(320+150*cos(t),240+150*sin(t));
    }

    glEnd();

	glFlush();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Open GL main3.cpp");
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
