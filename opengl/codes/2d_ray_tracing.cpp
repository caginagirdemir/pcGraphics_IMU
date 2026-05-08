#include <gl/glut.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
using namespace std; 
  
// This pair is used to store the X and Y 
// coordinates of a point respectively 
#define pdd pair<double, double> 


//////////////////////////////////////intersection belirleme

pdd lineLineIntersection(pdd A, pdd B, pdd C, pdd D) 
{ 
    // Line AB represented as a1x + b1y = c1 
    double a1 = B.second - A.second; 
    double b1 = A.first - B.first; 
    double c1 = a1*(A.first) + b1*(A.second); 
  
    // Line CD represented as a2x + b2y = c2 
    double a2 = D.second - C.second; 
    double b2 = C.first - D.first; 
    double c2 = a2*(C.first)+ b2*(C.second); 
  
    double determinant = a1*b2 - a2*b1; 
  
    if (determinant == 0) 
    { 
        // The lines are parallel. This is simplified 
        // by returning a pair of FLT_MAX 
        return make_pair(FLT_MAX, FLT_MAX); 
    } 
    else
    { 
        double x = (b2*c1 - b1*c2)/determinant; 
        double y = (a1*c2 - a2*c1)/determinant; 
        return make_pair(x, y); 
    } 
} 

//////////////////////////intersection belirleme



//////////////////random functions
struct Point_new {
   float x, y, a;
};

pdd points[240];
Point_new last_point[240];
float sortByAngle[240];
bool compareInterval(Point_new i1, Point_new i2) 
{ 
    return (i1.a < i2.a); 
} 


void randomPoints(int n, int width, int height) 
{

  for(int i=0; i<n; i++){
   points[i].first = rand()%((width - 0) + 1) + 0;;
   points[i].second = rand()%((height - 0) + 1) + 0;
  }
}

////////////////////////////////









/////////////////////////////////////////isolated intersection check
struct Point {
   int x, y;
};

struct line {
   Point p1, p2;
};

bool onLine(line l1, Point p) {   //check whether p is on the line or not
   if(p.x <= std::max(l1.p1.x, l1.p2.x) && p.x <= std::min(l1.p1.x, l1.p2.x) &&
      (p.y <= std::max(l1.p1.y, l1.p2.y) && p.y <= std::min(l1.p1.y, l1.p2.y)))
      return true;
   
   return false;
}

int direction(Point a, Point b, Point c) {
   int val = (b.y-a.y)*(c.x-b.x)-(b.x-a.x)*(c.y-b.y);
   if (val == 0)
      return 0;     //colinear
   else if(val < 0)
      return 2;    //anti-clockwise direction
      return 1;    //clockwise direction
}

bool isIntersect(line l1, line l2) {
   //four direction for two lines and points of other line
   int dir1 = direction(l1.p1, l1.p2, l2.p1);
   int dir2 = direction(l1.p1, l1.p2, l2.p2);
   int dir3 = direction(l2.p1, l2.p2, l1.p1);
   int dir4 = direction(l2.p1, l2.p2, l1.p2);
   
   if(dir1 != dir2 && dir3 != dir4)
      return true; //they are intersecting

   if(dir1==0 && onLine(l1, l2.p1)) //when p2 of line2 are on the line1
      return true;

   if(dir2==0 && onLine(l1, l2.p2)) //when p1 of line2 are on the line1
      return true;

   if(dir3==0 && onLine(l2, l1.p1)) //when p2 of line1 are on the line2
      return true;

   if(dir4==0 && onLine(l2, l1.p2)) //when p1 of line1 are on the line2
      return true;
         
   return false;
}

/////////////////////////////////////////isolated intersection check






void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
}

//line structure
typedef struct linee
{
	float x1;
	float y1;
	float x2;
	float y2;
}Lines; 


//degiskenler
Lines polygon_lines[240];
Lines ray_lines[240];

float result;
float intersection_X, intersection_Y;
float* results = new float[2];
float point_x[240],point_y[240],q_point_x,q_point_y;
int counter,edgenumber=0;
bool draw_flag,last_line_flag,stage_2_flag,draw_stage_2,draw_3_flag,last_line_flag_file,q_point_flag,random_flag,draw_polygon_flag=0;








void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	//mouse ile runtime cizim
	if(draw_flag)
	{
	glBegin(GL_LINES);
	for(int i=1;i<counter;i++)
	{
	glVertex2i(point_x[counter-(i+1)], point_y[counter-(i+1)]);
	glVertex2i(point_x[counter-i], point_y[counter-i]);
	}
	glEnd();
	glFlush();
	}
	
	if(random_flag)
	{
		
		counter=edgenumber;
		
		randomPoints(counter,640,480);

	  	for(int i=0; i<=counter; i++){
	  	sortByAngle[i] = atan2(points[i].second - 240, points[i].first - 320)* 180 / M_PI;
      	}	
      
    	for(int i=0; i<counter; i++){
    		
    		last_point[i].x = points[i].first;
    		last_point[i].y = points[i].second;
    		last_point[i].a = sortByAngle[i];
    		}
      
    	sort(last_point, last_point+counter, compareInterval); 
    	
    	for(int i=0; i<=counter; i++){
    		point_x[i] = last_point[i].x;
    		point_y[i] = last_point[i].y;
    	}
    	
//    	glBegin(GL_LINE_LOOP);
//		for(int j=0;j<counter;j++)
//		{
//		glVertex2i(last_point[j].x, last_point[j].y);
//		}
//		glEnd();
//		glFlush();
		
    	for(int i=0; i<counter; i++){
		std::cout << i << "  " << last_point[i].x << "  "<< last_point[i].y << "  " << last_point[i].a << std::endl;
	  	}
    	
    	
		
		last_line_flag=1;
		random_flag=0;
	}
	
	//cizgi tamamlama
	if (last_line_flag)
	{
		glBegin(GL_LINE_LOOP);
		for(int j=0;j<counter;j++)
		{
		glVertex2i(point_x[j], point_y[j]);
		}
		glEnd();
		glFlush();
		q_point_flag=1;
	}
	

	//q noktasi secildikten sonra ray line cizimi ve polygon_lines intersection kontorlü
	if(stage_2_flag)
	{
		point_x[counter] = point_x[0];
		point_y[counter] = point_y[0];
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_LINE_LOOP);
		for(int j=0;j<counter;j++)
		{
		glVertex2i(point_x[j], point_y[j]);

		polygon_lines[j].x1 =	point_x[j];
		polygon_lines[j].y1 =	point_y[j];
		polygon_lines[j].x2 =	point_x[j+1];
		polygon_lines[j].y2 =	point_y[j+1];
		}
		glEnd();
		glColor3f(1.0,0.0,0.0);
		glPointSize(3.0);
		glBegin(GL_POINTS);
		glVertex2i(q_point_x, q_point_y);
		glEnd();

		
		for(int k=0;k<counter;k++)
		{
		ray_lines[k].x1 =	q_point_x;
		ray_lines[k].y1 =	q_point_y;
		ray_lines[k].x2 =	point_x[k];
		ray_lines[k].y2 =	point_y[k];
		}
		
		if(draw_stage_2)
		{
		glBegin(GL_LINES);
		for(int i=0;i<counter;i++)
		{
			glVertex2i(q_point_x, q_point_y);
			glVertex2i(point_x[i], point_y[i]);
		}
		glEnd();
		std::cout<<"q noktasi"<<q_point_x<<" "<<q_point_y<<std::endl;
		
		
		
		for(int i=0;i<counter;i++)
		{

			for(int p=0;p<counter;p++)
			{
				line l1 = {{ray_lines[i].x1,ray_lines[i].y1}, {ray_lines[i].x2, ray_lines[i].y2}};
   				line l2 = {{polygon_lines[p].x1,polygon_lines[p].y1}, {polygon_lines[p].x2, polygon_lines[p].y2}};
   
  				 if(isIntersect(l1, l2))
  				 	if(ray_lines[i].x2 == polygon_lines[p].x1 || ray_lines[i].x2 == polygon_lines[p].x2 && ray_lines[i].y2 == polygon_lines[p].y1 || ray_lines[i].y2==polygon_lines[p].y2)
      				{
      					 std::cout << i << "ray Lines are not intersecting"<<std::endl;
					}
					else
					{
						std::cout << i << "ray Lines are intersecting"<<std::endl;
						glColor3f(0.0,1.0,0.0);
						glBegin(GL_LINES);
						glVertex2i(ray_lines[i].x1,ray_lines[i].y1);
						glVertex2i(ray_lines[i].x2,ray_lines[i].y2);
						glEnd();

						ray_lines[i].x1 = 0;
						ray_lines[i].x2 = 0;
						ray_lines[i].y1 = 0;
						ray_lines[i].y2 = 0;
						glColor3f(1.0,1.0,1.0);
					}
					  
  				 else
   				    std::cout << i << "ray Lines are not intersecting"<<std::endl;
		}
		}

		}
		glFlush();
	}
	
	
	if(draw_3_flag)
	{
		float intersection_X, intersection_Y;
		
		glFlush();
		glColor3f(1.0,0.0,0.0);
		glPointSize(3.0);
		glBegin(GL_POINTS);
		glVertex2i(q_point_x, q_point_y);
		glEnd();

		glBegin(GL_LINES);
		for(int i=0;i<counter;i++)
		{
		glVertex2i(ray_lines[i].x1,ray_lines[i].y1);
		glVertex2i(ray_lines[i].x2,ray_lines[i].y2);
		}
		glEnd();
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_LINE_LOOP);
		for(int j=0;j<counter;j++)
		{
		glVertex2i(point_x[j], point_y[j]);
		}
		glEnd();
		glFlush();
		
		for(int i=0;i<counter;i++)
		{
			if(ray_lines[i].x1 != 0)
			{
				for(int j=0;j<counter;j++)
				{
				pdd A = make_pair(ray_lines[i].x1, ray_lines[i].y1); 
   				pdd B = make_pair(ray_lines[i].x2, ray_lines[i].y2); 
    			pdd C = make_pair(polygon_lines[j].x1, polygon_lines[j].y1); 
    			pdd D = make_pair(polygon_lines[j].x2, polygon_lines[j].y2);
				
				pdd intersection = lineLineIntersection(A, B, C, D); //yesil ray_line lar atildiktan sonra ray_line ve polygon_line kesisme noktalari
  
    			if (intersection.first == FLT_MAX && 
    		    intersection.second==FLT_MAX) 
    			{ 
       				 cout << "The given lines AB and CD are parallel.\n"; 
    			} 
				else
    			{ 
        			intersection_X = intersection.first;
        			intersection_Y = intersection.second;
        			line l1 = {{intersection_X+1,intersection_Y-1}, {intersection_X-1, intersection_Y+1}};
   					line l2 = {{polygon_lines[j].x1,polygon_lines[j].y1}, {polygon_lines[j].x2, polygon_lines[j].y2}};
					if(isIntersect(l1, l2)) //kesisme noktasi o polygon_line üzerinde mi
					{
						if(intersection_X == ray_lines[i].x2 || intersection_Y == ray_lines[i].y2) //kesisme noktasi ray_line ucuna denk gelmemesi gerek bunun kontrolü
      					{	

      					}
      					else
      					{
      						float distance_a; //
      						float distance_b;
      						distance_a = sqrt(pow(q_point_x - intersection_X, 2) +  pow(q_point_y - intersection_Y, 2) * 1.0); 
      						//distance_a = intersection_X intersection_Y q_point_x q_point_y // kesime noktasinin q_point uzakligi
      						distance_b = sqrt(pow(ray_lines[i].x2 - intersection_X, 2) +  pow(ray_lines[i].y2 - intersection_Y, 2) * 1.0); 
      						//distance_b = intersection_X intersection_Y ray_lines[i].x2 ray_lines[i].y2 //kesisme noktasinin ray_line uc uzakligi
      						if(distance_b<distance_a) //kesisme noktasi ray_line ucuna daha uzak olmak zorunda yoksa polygon_line i tersten kesmis demektir.
      						{
      						glLineWidth(3);	
							glColor3f(0.0,0.0,1.0);
							glBegin(GL_LINES);
							glVertex2i(ray_lines[i].x2, ray_lines[i].y2);
							glVertex2i(intersection_X, intersection_Y);	
							glEnd();
							ray_lines[i].x2 = intersection_X;
							ray_lines[i].y2 = intersection_Y;
							glColor3f(1.0,1.0,1.0);
													

							}
						

						}


					}
        			
    			} 
				}
			}
		}
		

	glFlush();	
	}
	
	if(draw_polygon_flag)
	{
		glColor3f(1.0,0.0,0.0);
		glPointSize(3.0);
		glBegin(GL_POINTS);
		glVertex2i(q_point_x, q_point_y);
		glEnd();
		for(int i=0;i<counter;i++)
		{
			if(ray_lines[i].x1 != 0)
			{
				glColor3f(1.0,1.0,0.0);
				glBegin(GL_LINES);
				glVertex2i(ray_lines[i].x1, ray_lines[i].y1);
				glVertex2i(ray_lines[i].x2, ray_lines[i].y2);
				glEnd();
				

				
			}
		}
		
		

		glFlush();
	}
	
	
}


void OnMouseClick(int button, int state, int x, int y)
{
if(!q_point_flag)
{

if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
{ 
 	std::cout<<x<<" "<<480-y<<std::endl;
 	point_x[counter] = x;
  	point_y[counter] = 480-y;
  	counter++;
  	if(counter>=2)
	{
	draw_flag=1;
	}
}
}
else
{
	q_point_x = x;
  	q_point_y = 480-y;
  	stage_2_flag=1;
}
}


void mainMenuHandler(int choice) {
	
	if(choice == 0)
	{
	draw_flag=0;
	last_line_flag=1;
	display();
	}
	if(choice == 3) {
	std::ofstream myfile;
	myfile.open ("points.txt");
	myfile << q_point_x << " " << q_point_y << "\n";
 	for(int i=0;i<counter;i++)
	{
	  	myfile << point_x[i] <<" "<< point_y[i] << "\n";	
	}

  	myfile.close();
	}
	if(choice==4)
	{
		draw_flag=0;
		last_line_flag=1;
		stage_2_flag=0;
		draw_3_flag = 1;
		display();
	}
	
	if(choice==7)
	{
		draw_flag=0;
		last_line_flag=1;
		stage_2_flag=0;
		draw_3_flag = 0;
		draw_polygon_flag=1;
		display();
	}
	
	
	if(choice==6)
	{
		loop:std::cout<< "enter edge number" << std::endl;
		std::cin >> edgenumber;
		if(edgenumber<4)
		{
			std::cout<< "must be least 4" << std::endl;
			goto loop;
		}
		draw_flag=0;
		random_flag=1;
		display();
	}
	
	if(choice==5)
	{
	 std::ifstream myReadFile;
	 myReadFile.open("points.txt");
	 if (myReadFile.is_open()) {
	counter=0;
	myReadFile >> q_point_x >> q_point_y;
	while(!myReadFile.eof())
	{
	    myReadFile >>  point_x[counter] >> point_y[counter];
	    counter++;
	 }
	}
	else
	{
		std::cout<<"dosya bulunamadi.";
	}
	myReadFile.close();
	counter--;
	draw_flag=0;
	last_line_flag=1;
	stage_2_flag=1;
	display();
	}
}

void subMenuHandler(int choice) {
	
	if(choice) draw_stage_2=1;
	else draw_stage_2=0;
	display();
}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	

	
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	
	glutCreateWindow("BCA 608");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(OnMouseClick);
	
	int subMenu = glutCreateMenu(subMenuHandler);
	glutAddMenuEntry("on", 1);
	glutAddMenuEntry("off", 0);


	
	glutCreateMenu(mainMenuHandler);
	glutAddMenuEntry("line_loop", 0);
	glutAddMenuEntry("save text", 3);
	glutAddMenuEntry("load text", 5);
	glutAddMenuEntry("random polygon", 6);
	glutAddMenuEntry("draw polygon", 7);
	glutAddSubMenu("draw_2", subMenu);
	glutAddMenuEntry("draw_3", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}


