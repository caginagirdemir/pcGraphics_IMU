#include <iostream>

#include <GL/freeglut.h>

#include <math.h>

#include <Eigen/Dense>

using namespace Eigen;

bool flag = 0;

//points
int max = 20;
float points[20][3];
int sayi=0;
float Px =0;
float Py =0;
float Pz =0;
float mx = 0;
float my = 0;
float mz = 0;
float a[3][20];
float a_t[20][3];
float C[3][3];

void drawScene(void)
{
	



	
	
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	
	for(int j = 0; j < max; j++)
	{
	glPushMatrix ();
	glTranslatef(points[j][0], points[j][1], -5.0);
	glColor3f(1.0, 0.0, 0.0);
	glutWireSphere(0.1, 16, 10);
	glPopMatrix ();
	}
	
	
	glutSwapBuffers();
	
	//average matrix
	for(int k = 0; k < max; k++)
	{
	Px = Px + points[k][0];	
	Py = Py + points[k][1];
	Pz = Pz + points[k][2];			
	}
	
	mx = Px/max;
	my = Py/max;
	mz = Pz/max;
	
	//deviation matrix
	for(int j = 0; j < max; j++)
	{
	a[0][j] = points[j][0] - mx;
	a[1][j] = points[j][1] - my;
	a[2][j] = points[j][2] - mz;
	}
	

	
	for(int i = 0; i < max; i++)
	{
		
		a_t[i][0] = a[0][i];
		a_t[i][1] = a[1][i];
		a_t[i][2] = a[2][i];
	}
	
	
	for(int P = 0; P < max; P++)
	{
	C[0][0] = C[0][0] + a_t[P][0] * a[0][P];
	C[0][1] = C[0][1] + a_t[P][1] * a[0][P];
	C[0][2] = C[0][2] + a_t[P][2] * a[0][P];
	
	C[1][0] = C[1][0] + a_t[P][0] * a[1][P];
	C[1][1] = C[1][1] + a_t[P][1] * a[1][P];
	C[1][2] = C[1][2] + a_t[P][2] * a[1][P];
	
	C[2][0] = C[2][0] + a_t[P][0] * a[2][P];
	C[2][1] = C[2][1] + a_t[P][1] * a[2][P];
	C[2][2] = C[2][2] + a_t[P][2] * a[2][P];
	}
	
	C[0][0] = C[0][0] / max;
	C[0][1] = C[0][1] / max;
 	C[0][2] = C[0][2] / max;
                  
	C[1][0] = C[1][0] / max;
	C[1][1] = C[1][1] / max;
 	C[1][2] = C[1][2] / max;
                  
 	C[2][0] = C[2][0] / max;
	C[2][1] = C[2][1] / max;
 	C[2][2] = C[2][2] / max;

 
    Matrix3f A;
   A << C[0][0], C[0][1], C[0][2], C[1][0], C[1][1], C[1][2], C[2][0], C[2][1], C[2][2];
   std::cout << "Here is the matrix A:\n" << A << "\n";
   SelfAdjointEigenSolver<Matrix3f> eigensolver(A);
   if (eigensolver.info() != Success) abort();
   std::cout << "The eigenvalues of A are:\n" << eigensolver.eigenvalues() << "\n";
   std::cout << "Here's a matrix whose columns are eigenvectors of A \n"
        << "corresponding to these eigenvalues:\n"
        << eigensolver.eigenvectors() << "\n" ;

 
 
}
 
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}
 
// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-100.0, 100.0, -100.0, 100.0, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char **argv)
{





for(int i = 0; i < max; i++)
{
	
	points[i][0] = rand() % 100;
	sayi = rand() %2 ;
	if(sayi% 2)
	{
		points[i][0] = points[i][0]*-1;
	}
	points[i][1] = rand() % 100;
	sayi = rand() %2;
	if(sayi% 2)
	{
		points[i][1] = points[i][1]*-1;
	}
	points[i][2] = rand() % 100;
	sayi = rand() %2;
	if(sayi% 2)
	{
		points[i][2] = points[i][2]*-1;
	}
}


for(int i = 0; i < max; i++)
{
	std::cout << points[i][0] << "  " << points[i][1] << "  " << points[i][2] << "\n";
}
	std::cout << "-------\n";
	
	
	
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("moveSphere.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);



	setup();

	glutMainLoop();
	
	
	
}
