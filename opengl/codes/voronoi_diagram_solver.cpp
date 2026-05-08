#include <gl/glut.h>
#include <math.h>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;

#define PI 3.14159265

struct Point {
   float x, y;
};

struct Point_W_Color {
	int x,y;
   float red, green, blue;
};

void init() {

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
	
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0.0,0.0,0.0,0.0);
}

int click_count = 0;

int global_r=20;
float sort_distances[240];
float unsorted_distances[240];
Point_W_Color points[240];

Point grid_p[240][240];
//Colors grid_p_color[240][240];
float x =5;
float y = 480;
int s=0;

void drawbox(float r) 
{ 

int count_x = 640/r;
int count_y = 480/r;
glColor3f(1.0,1.0,1.0);
	for(int j=0;j<count_y;j++)
	{
		for(int i=0;i<count_x;i++)
		{
		glBegin(GL_LINE_LOOP);
		glVertex2f(x+i*r, y-j*r);
		glVertex2f(x+r+i*r, y-j*r);
		glVertex2f(x+r+i*r, y-r-j*r);
		glVertex2f(x+i*r, y-r-j*r);
		glEnd();
		
		glBegin(GL_POINTS);
		glVertex2f(x+i*r+r/2, y-(j*r)-(r/2));
		glEnd();
		
		grid_p[i][j].x=x+i*r+r/2;
		grid_p[i][j].y=y-(j*r)-(r/2);
		}
	}

	


}

float distance(int x1, int y1, int x2, int y2) 
{ 
    // Calculating distance 
    return sqrt(pow(x2 - x1, 2) +  
                pow(y2 - y1, 2) * 1.0); 
} 


void display(void) {

	drawbox(global_r);
	glFlush();
}

Point intersect;
void OnMouseClick(int button, int state, int x, int y)
{


if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
{

	points[click_count].x = x;
	points[click_count].y = y;
	s =points[0].x;
	float red = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float green = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float blue = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	points[click_count].red = red;
	points[click_count].green = green;
	points[click_count].blue = blue;
		
	
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

	
	glColor3f(0.0,0.0,0.0);
		for(int j=0;j<480/global_r;j++)
		{
		for(int i=0;i<640/global_r;i++)
			{
			glBegin(GL_POLYGON);		
			glVertex2f(grid_p[i][j].x-global_r/2, grid_p[i][j].y+global_r/2);
			glVertex2f(grid_p[i][j].x-global_r/2+global_r,grid_p[i][j].y+global_r/2);
			glVertex2f(grid_p[i][j].x-global_r/2+global_r,grid_p[i][j].y+global_r/2-global_r);
			glVertex2f(grid_p[i][j].x-global_r/2,grid_p[i][j].y+global_r/2-global_r);
			glEnd();
	}}

	
		for(int j=0;j<480/global_r;j++)
		{
		for(int i=0;i<640/global_r;i++)
			{
				if(click_count != 0)
				{

				for(int p=0;p<=click_count;p++)
				{
					sort_distances[p] = distance(grid_p[i][j].x,grid_p[i][j].y,points[p].x,480-points[p].y);
					unsorted_distances[p] = sort_distances[p];
				}
				int n = sizeof(sort_distances) / sizeof(sort_distances[0]); 
				sort(sort_distances, sort_distances + n);
				
				for(int p=0;p<=click_count;p++)
				{
					if(unsorted_distances[p] == sort_distances[0])
					{
						glColor4f(points[p].red,points[p].green,points[p].blue,0.5);
						glBegin(GL_POLYGON);
						glVertex2f(grid_p[i][j].x-global_r/2, grid_p[i][j].y+global_r/2);
						glVertex2f(grid_p[i][j].x-global_r/2+global_r,grid_p[i][j].y+global_r/2);
						glVertex2f(grid_p[i][j].x-global_r/2+global_r,grid_p[i][j].y+global_r/2-global_r);
						glVertex2f(grid_p[i][j].x-global_r/2,grid_p[i][j].y+global_r/2-global_r);
						glEnd();
					}
				}
				 
				}
				else
				{
					
				}
			}
		}
	
	
	if(click_count<1)
	{
		
		
		for(int j=0;j<480/global_r;j++)
		{
		for(int i=0;i<640/global_r;i++)
			{
		glBegin(GL_POLYGON);
		glColor4f(points[0].red,points[0].green,points[0].blue,0.5);
		glVertex2f(grid_p[i][j].x-global_r/2, grid_p[i][j].y+global_r/2);
		glVertex2f(grid_p[i][j].x-global_r/2+global_r,grid_p[i][j].y+global_r/2);
		glVertex2f(grid_p[i][j].x-global_r/2+global_r,grid_p[i][j].y+global_r/2-global_r);
		glVertex2f(grid_p[i][j].x-global_r/2,grid_p[i][j].y+global_r/2-global_r);
		glEnd();
		}}
	}


			click_count++;


	
	glFlush();
	glColor3f(1.0,1.0,1.0);
	
	
}



}

void mainMenuHandler(int choice) {
points[click_count].x = 0;
points[click_count].y = 0;
click_count--;

	glColor3f(0.0,0.0,0.0);
		for(int j=0;j<480/global_r;j++)
		{
		for(int i=0;i<640/global_r;i++)
			{
			glBegin(GL_POLYGON);		
			glVertex2f(grid_p[i][j].x-global_r/2, grid_p[i][j].y+global_r/2);
			glVertex2f(grid_p[i][j].x-global_r/2+global_r,grid_p[i][j].y+global_r/2);
			glVertex2f(grid_p[i][j].x-global_r/2+global_r,grid_p[i][j].y+global_r/2-global_r);
			glVertex2f(grid_p[i][j].x-global_r/2,grid_p[i][j].y+global_r/2-global_r);
			glEnd();
			
	}}

			drawbox(global_r);


for(int j=0;j<480/global_r;j++)
		{
		for(int i=0;i<640/global_r;i++)
			{
				for(int p=0;p<=click_count;p++)
				{
					sort_distances[p] = distance(grid_p[i][j].x,grid_p[i][j].y,points[p].x,480-points[p].y);
					unsorted_distances[p] = sort_distances[p];
				}
				int n = sizeof(sort_distances) / sizeof(sort_distances[0]); 
				sort(sort_distances, sort_distances + n);
				
				for(int p=0;p<click_count;p++)
				{
					if(unsorted_distances[p] == sort_distances[0])
					{
					points[0].x=s;
					glColor3f(1.0,0.0,0.0);
					glBegin(GL_LINES);
					glVertex2f(grid_p[i][j].x,grid_p[i][j].y);
					glVertex2f(points[p].x, 480-points[p].y);
					glEnd();
					}
				}
				glColor3f(1.0,1.0,1.0);
				for(int i=0;i<=240;i++)
				{
					sort_distances[i] =1000;
					unsorted_distances[i] = 0;
				}
			}
		}

		glFlush();	
}



int main(int argc, char** argv)
{
	
	for(int i=0;i<=240;i++)
	{
		sort_distances[i] =1000;
	}
	std::cout <<"square distance \n";
	std::cin >> global_r;
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Open GL main8.cpp");
	init();
	
	glutCreateMenu(mainMenuHandler);
	glutAddMenuEntry("last_delete", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(display);
	glutMouseFunc(OnMouseClick);
	glutMainLoop();

	return 0;
}
