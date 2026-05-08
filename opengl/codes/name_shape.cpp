
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include<iostream>
#include<fstream>

float x[240],y[240],z[240];
GLfloat _x, _y, spin_x = 0, spin_y = 0;
void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)width/height, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(15, 0, 50, 15, 0, 0, 0, 1, 5);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
                glPolygonMode(GL_FRONT, GL_FILL);
            glPolygonMode(GL_BACK, GL_FILL);
}


void display(void)
{
    int i, k, swap = 0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(-10/2, 0, -10*2);
    glRotatef(spin_x, 0, 1, 0);
    glRotatef(spin_y, 1, 0, 0);
	//C
	glBegin(GL_POLYGON);
	for(int i = 0; i<16; i++)
	{
		glVertex3f(x[i], y[i], z[i]);
	}
	glEnd();
	
	glBegin(GL_POLYGON);
	for(int i = 16; i<32; i++)
	{
		glVertex3f(x[i], y[i], z[i]);
	}
	 glEnd();
	 
	glBegin(GL_POLYGON);
	for(int i = 32; i<48; i++)
	{
		glVertex3f(x[i], y[i], z[i]);
	}
	glEnd();

    glPopMatrix();

    glPushMatrix();   
	glTranslatef(5, 0, -10*2);
    glRotatef(spin_x, 0, 1, 0);
    glRotatef(spin_y, 1, 0, 0);
	//A
    glBegin(GL_POLYGON);
	for(int i = 48; i<64; i++)
	{
		glVertex3f(x[i], y[i], z[i]);
	}
    glEnd();
    
    glBegin(GL_POLYGON);
	for(int i = 64; i<80; i++)
	{
		glVertex3f(x[i], y[i], z[i]);
	}
    glEnd();
    
    glBegin(GL_POLYGON);
	for(int i = 80; i<96; i++)
	{
		glVertex3f(x[i], y[i], z[i]);
	}
    glEnd();
    
	glBegin(GL_POLYGON);
	for(int i = 96; i<112; i++)
	{
		glVertex3f(x[i], y[i], z[i]);
	}
	glEnd();
	
	glPopMatrix();
	//G
	glPushMatrix();   
	glTranslatef(15, 0, -10*2);
    glRotatef(spin_x, 0, 1, 0);
    glRotatef(spin_y, 1, 0, 0);
	glBegin(GL_POLYGON);
	for(int i = 112; i<128; i++)
	{
		glVertex3f(x[i], y[i], z[i]);
	}
	glEnd();
	
    glBegin(GL_POLYGON);
	for(int i = 128; i<144; i++)
	{
		glVertex3f(x[i], y[i], z[i]);
	}
    glEnd();
    
   	glBegin(GL_POLYGON);
	for(int i = 144; i<160; i++)
	{
		glVertex3f(x[i], y[i], z[i]);
	}
	glEnd();
	
	glBegin(GL_POLYGON);
	for(int i = 160; i<176; i++)
	{
		glVertex3f(x[i], y[i], z[i]);
	}
    glEnd();
	
	glPopMatrix();
	
	
	//I
	glPushMatrix();   
	glTranslatef(25, 0, -10*2);
    glRotatef(spin_x, 0, 1, 0);
    glRotatef(spin_y, 1, 0, 0);
    glBegin(GL_POLYGON);
	for(int i = 176; i<192; i++)
	{
		glVertex3f(x[i], y[i], z[i]);
	}
    glEnd();

	glPopMatrix();
	
	
	//N
	glPushMatrix();   
	glTranslatef(30, 0, -10*2);
    glRotatef(spin_x, 0, 1, 0);
    glRotatef(spin_y, 1, 0, 0);
    glBegin(GL_POLYGON);
	for(int i = 192; i<208; i++)
	{
		glVertex3f(x[i], y[i], z[i]);
	}
    glEnd();

    glBegin(GL_POLYGON);
	for(int i = 208; i<224; i++)
	{
		glVertex3f(x[i], y[i], z[i]);
	}
    glEnd();
    
    
    glBegin(GL_POLYGON);
	for(int i = 224; i<240; i++)
	{
		glVertex3f(x[i], y[i], z[i]);
	}
    glEnd();
	glPopMatrix();
    glutSwapBuffers();
    

}


void keyboard(unsigned char key, int x, int y)
{
    static int wire = 0;

    if (key == 27) {
        exit(0);
    } else if (key == 'w' || key == 'W')  {
        wire ^= 1;
        if (wire)
        {
            glPolygonMode(GL_FRONT, GL_LINE);
            glPolygonMode(GL_BACK, GL_LINE);
            		}
        else
        {
            glPolygonMode(GL_FRONT, GL_FILL);
            glPolygonMode(GL_BACK, GL_FILL);
        }
    } 

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    _x = x;
    _y = y;

    glutPostRedisplay();
}

void motion(int x, int y)
{
    spin_x = x - _x;
    spin_y = y - _y;

    glutPostRedisplay();
}



int main(int argc, char** argv)
{
	
	
	
 std::ifstream myReadFile;
 myReadFile.open("C:/name.dat");
 
 if (myReadFile.is_open()) {
for (int i=0; i<241; i++){
    myReadFile >> x[i] >> y[i] >> z[i];
 }
}
myReadFile.close();



    int i, k;

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(600, 800);
    glutInit(&argc, argv);

    glutCreateWindow("soru4");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
