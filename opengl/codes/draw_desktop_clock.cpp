#include <gl/glut.h>
#include <math.h>
#include <iostream>
#define PI 3.14159265
void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
}
void DrawArc(float x, float y, float r, float start_angle, float end_angle) 
{ 
glBegin(GL_LINE_STRIP);
    double angle_increment = PI / 1000;
    for (double theta = start_angle; theta < end_angle; theta += angle_increment)
    {
        glVertex2d(x+  r * cos(theta), y+ r * sin(theta));
    }
    glEnd();
}
void display(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	DrawArc(320,240,70,0,2*PI); //P1 noktasýndan 70 birimlik tam cember (0->2*PI)
	DrawArc(320,240,80,0,PI); //P1 noktasindan 80 birimlik yarim cember (0->PI)
	DrawArc(160,240,80,3*PI/2,2*PI); //P2 noktasindan 80 birimlik ceyrek cember (3*PI/2->2*PI)
	DrawArc(480,240,80,PI,3*PI/2); //P3 noktasindan 80 birimlik ceyrek cember (PI->3*PI/2)
	glBegin(GL_LINE_STRIP);
	glVertex2f(160.0,160.0);
	glVertex2f(100.0,160.0);
	glVertex2f(100.0,50.0);
	glVertex2f(540.0,50.0);
	glVertex2f(540.0,160.0);
	glVertex2f(480.0,160.0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2f(320.0,240.0);
	float x1 = 320+  70 * cos(PI/1.5);
	float y1 = 240+ 70 * sin(PI/1.5);
	glVertex2f(x1, y1);
	//ok çizdirme kýsmý
	glVertex2f(x1, y1-10); 
	glVertex2f(x1+10, y1-3);
	glVertex2f(x1, y1);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2f(320.0,240.0);
	float x2 = 320+  50 * cos(PI/7);
	float y2 = 240+ 50 * sin(PI/7);
	glVertex2f(x2, y2);
	glEnd();
	glFlush();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Open GL main8.cpp");
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
