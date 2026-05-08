#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <fstream>
//-----------------file read function
void drawPolyLineFile(const char * fileName) {

	std::ifstream inStream;
	inStream.open(fileName);	// open the file
	if(inStream.fail())
		return;
	glClear(GL_COLOR_BUFFER_BIT);      // clear the screen 
	GLint numpolys, numLines, x ,y;
	inStream >> numpolys;		           // read the number of polylines
	for(int j = 0; j < numpolys; j++)  // read each polyline
	{
		inStream >> numLines;
		glBegin(GL_LINE_STRIP);	     // draw the next polyline
		for (int i = 0; i < numLines; i++)
		{
			inStream >> x >> y;        // read the next x, y pair
			glVertex2i(x, y);
		}
		glEnd();
	}
	glFlush();
	inStream.close();
}

//--------------- setWindow ---------------------
void setWindow(float left, float right, int bottom, int top)
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(left, right, bottom, top); 
}
//---------------- setViewport ------------------
void setViewport(int left, int bottom, int width, int height)
{
glViewport(left, bottom, width, height);
drawPolyLineFile("/Users/Ogrenci/Desktop/dino.dat"); //draw function use in setViewport function
}


void render() {

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0); //set color white
	setWindow(0,640,0,500); //set new window
	for(int i=0;i<500;i+=100)  //loop 1
	{
		for(int j=0;j<600;j+=120) //loop 2
		{
				setViewport(j, i, 120, 100); //both setViewport and draw function
				setViewport(j, i, 120, 100);
				setViewport(j, i, 120, 100);
				setViewport(j, i, 120, 100);
				setViewport(j, i, 120, 100);
		}
	}

	glFlush();

}
//--------------window settings
int main(int argc, char** argv)
{
	glutInit( &argc, argv ); 
	
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize( 640,500 );
	glutInitWindowPosition( 0, 0 );
	glutCreateWindow( "Poly Line main4.cpp" );
	
	glutDisplayFunc( render );;                   
	glutMainLoop();

	return( 0 );

}
