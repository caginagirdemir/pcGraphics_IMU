
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>


GLfloat mesh[10][10];

GLfloat old_x, old_y, rot_x = 0, rot_y = 0;
 int wire = 0;
void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)width/height, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 20, 0, 0, 0, 0, 1, 5);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_BACK, GL_LINE);
}


void display(void)
{
int i, k, swap = 0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(-10/2, 0, -10*2);
    glRotatef(rot_x, 0, 1, 0);
    glRotatef(rot_y, 1, 0, 0);

    glColor3f(255, 255, 255);
    glBegin(GL_TRIANGLE_STRIP);
    for (k = 0; k < 10-1; k++) {
        if (swap) {
            for (i = 10-1; i >= 0; i--) {
                glColor3f(255, 0, 0);
                glVertex3f(i, mesh[k][i], k);
                glColor3f(0, 0, 255);
                glVertex3f(i, mesh[k+1][i], k+1);
                if (i == 0) //ilk ücgen mi degil mi check
                    glVertex3f(i, mesh[k+1][i], k+1); 
            }
        } else {
            for (i = 0; i < 10; i++) {
                glColor3f(255, 0, 0);
                glVertex3f(i, mesh[k][i], k);
                glColor3f(0, 0, 255);
                glVertex3f(i, mesh[k+1][i], k+1);
                if (i == 10-1)
                    glVertex3f(i, mesh[k+1][i], k+1);
            }
        }
        swap ^= 1;
    }
    glEnd();

    glPopMatrix();

    glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y)
{

    if (key == 27) {
        exit(0);
    } else if (key == 'w' || key == 'W') {
        wire ^= 1;
        if (wire)
        {
        	glPolygonMode(GL_FRONT, GL_LINE);
        	glutPostRedisplay();
		}
        else
        {   
			glPolygonMode(GL_FRONT, GL_FILL);
			glutPostRedisplay();
		}

    } else if (key == 'c' || key == 'C') {

    	rot_x = 180 - old_x;
    	rot_y = 180 - old_y;
    	glutPostRedisplay();

    }
    else if (key == 'r' || key == 'R') {

    	rot_x = old_x;
    	rot_y = old_y;
    	glutPostRedisplay();

    }


}




int main(int argc, char** argv)
{
    int i, k;

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(600, 800);
    glutInit(&argc, argv);

    for (k = 0; k < 10; k++) {
        for (i = 0; i < 10; i++) {
            mesh[k][i] = sin((float)(i+k)/10*3.1415)*3;
        }
    }

    glutCreateWindow("soru1");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
