#include <gl/glut.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
#include <stack> 
#include <stdlib.h>
#include <stdio.h> 
#include <string.h> 
#include <climits>  
#define PI 3.14159265
#define pdd pair<double, double> 
#define INF 10000 
using namespace std; 
  
//structure
struct Point {
   float x, y;
};

struct perpendicular_point_distance {
   float perp_x, perp_y, distance;
};

struct line {
   Point p1, p2;
};

float distance(int x1, int y1, int x2, int y2) 
{ 
    // Calculating distance 
    return sqrt(pow(x2 - x1, 2) +  
                pow(y2 - y1, 2) * 1.0); 
} 

struct Point_new {
   float x, y, a;
};

//////////////////////////////////////////////////////

pair<float, float> find_Centroid(float vr_X[], float vr_Y[], int array_size) 
{ 
    std::pair<float, float> ans = { 0, 0 }; 
      
    int n = array_size; 
    float signedArea = 0; 
      
    // For all vertices 
    for (int i = 0; i < n; i++) { 
          
        float x0 = vr_X[i], y0 = vr_Y[i]; 
        float x1 = vr_X[(i + 1) % n], y1 =  
                            vr_Y[(i + 1) % n]; 
                              
        // Calculate value of A 
        // using shoelace formula 
        float A = (x0 * y1) - (x1 * y0); 
        signedArea += A; 
          
        // Calculating coordinates of 
        // centroid of polygon 
        ans.first += (x0 + x1) * A; 
        ans.second += (y0 + y1) * A; 
    } 
  
    signedArea *= 0.5; 
    ans.first = (ans.first) / (6 * signedArea); 
    ans.second = (ans.second) / (6 * signedArea); 
  
    return ans; 
} 

///////////////////////////////////////

Point_new last_point[240];
int subMenu;
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

//////////////////////////////////////

// point q lies on line segment 'pr' 
bool onSegment(Point p, Point q, Point r) 
{ 
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && 
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
        return true; 
    return false; 
} 
  
// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(Point p1, Point q1, Point r1) 
{ 
    int val = (q1.y - p1.y) * (r1.x - q1.x) - 
              (q1.x - p1.x) * (r1.y - q1.y); 
  
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 
  
// The function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
bool doIntersect(Point p1, Point q1, Point p2, Point q2) 
{ 
    // Find the four orientations needed for general and 
    // special cases 
    int o1 = orientation(p1, q1, p2); 
    int o2 = orientation(p1, q1, q2); 
    int o3 = orientation(p2, q2, p1); 
    int o4 = orientation(p2, q2, q1); 
  
    // General case 
    if (o1 != o2 && o3 != o4) 
        return true; 
  
    // Special Cases 
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1 
    if (o1 == 0 && onSegment(p1, p2, q1)) return true; 
  
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1 
    if (o2 == 0 && onSegment(p1, q2, q1)) return true; 
  
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2 
    if (o3 == 0 && onSegment(p2, p1, q2)) return true; 
  
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2 
    if (o4 == 0 && onSegment(p2, q1, q2)) return true; 
  
    return false; // Doesn't fall in any of the above cases 
} 
  
// Returns true if the point p lies inside the polygon[] with n vertices 
bool isInside(Point polygon[], int n, Point p) 
{ 
    // There must be at least 3 vertices in polygon[] 
    if (n < 3)  return false; 
  
    // Create a point for line segment from p to infinite 
    Point extreme = {INF, p.y}; 
  
    // Count intersections of the above line with sides of polygon 
    int count = 0, i = 0; 
    do
    { 
        int next = (i+1)%n; 
  
        // Check if the line segment from 'p' to 'extreme' intersects 
        // with the line segment from 'polygon[i]' to 'polygon[next]' 
        if (doIntersect(polygon[i], polygon[next], p, extreme)) 
        { 
            // If the point 'p' is colinear with line segment 'i-next', 
            // then check if it lies on segment. If it lies, return true, 
            // otherwise false 
            if (orientation(polygon[i], p, polygon[next]) == 0) 
               return onSegment(polygon[i], p, polygon[next]); 
  
            count++; 
        } 
        i = next; 
    } while (i != 0); 
  
    // Return true if count is odd, false otherwise 
    return count&1;  // Same as (count%2 == 1) 
} 



/////////////////////////////////////


pdd lineFromPoints(line l1,Point p) 
{ 
	pdd A = make_pair(l1.p1.x,l1.p1.y);
	pdd B = make_pair(l1.p2.x,l1.p2.y);
	
	double a1 = B.second - A.second; 
    double b1 = A.first - B.first; 
    double c1 = -1*(a1*(A.first) + b1*(A.second)); 
    

    
    double temp = -1 * (a1 * p.x + b1 * p.y + c1) / (a1 * a1 + b1 * b1); 
    double x = temp * a1 + p.x; 
    double y = temp * b1 + p.y;
    return make_pair(x, y); 
} 
  


bool onLine(line l1, Point p) {   //check whether p is on the line or not



}



void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);
	glPushAttrib(GL_ENABLE_BIT); 
}




//degiskenler
Point points[100];
Point p;
Point convex_hull_points[20];
line convex_hull_lines[100];
int counter=0; //points sayaci
bool point_lock = 0;
Point p0; 
int k,elastic_strip_count=0;
perpendicular_point_distance dist[10];
line elastic_strip_lines[100]; //ilk lastik diktörtgen line tanimlamasi
Point elastic_strip[100];
float sortByAngle[240];
int menuID;



Point nextToTop(stack<Point> &S) 
{ 
    Point p = S.top(); 
    S.pop(); 
    Point res = S.top(); 
    S.push(p); 
    return res; 
} 

int swap(Point &p1, Point &p2) 
{ 
    Point temp = p1; 
    p1 = p2; 
    p2 = temp; 
} 

int distSq(Point p1, Point p2) 
{ 
    return (p1.x - p2.x)*(p1.x - p2.x) + 
          (p1.y - p2.y)*(p1.y - p2.y); 
}

int orientation2(Point p, Point q, Point r) 
{ 
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y); 
  
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
} 

int compare(const void *vp1, const void *vp2) 
{ 
   Point *p1 = (Point *)vp1; 
   Point *p2 = (Point *)vp2; 
  
   // Find orientation 
   int o = orientation2(p0, *p1, *p2); 
   if (o == 0) 
     return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1; 
  
   return (o == 2)? -1: 1; 
} 

int convexHull(Point points[], int n) 
{ 
 
   int ymin = points[0].y, min = 0; 
   for (int i = 1; i < n; i++) 
   { 
     int y = points[i].y; 
  

     if ((y < ymin) || (ymin == y && 
         points[i].x < points[min].x)) 
        ymin = points[i].y, min = i; 
   } 
  

   swap(points[0], points[min]); 
  

   p0 = points[0]; 
   qsort(&points[1], n-1, sizeof(Point), compare); 
  

   int m = 1;
   for (int i=1; i<n; i++) 
   { 
       while (i < n-1 && orientation2(p0, points[i], 
                                    points[i+1]) == 0) 
          i++; 
  
  
       points[m] = points[i]; 
       m++;  
   } 
  

   if (m < 3) return 0; 
  
   stack<Point> S; 
   S.push(points[0]); 
   S.push(points[1]); 
   S.push(points[2]); 
  
   for (int i = 3; i < m; i++) 
   { 
      while (orientation2(nextToTop(S), S.top(), points[i]) != 2) 
         S.pop(); 
      S.push(points[i]); 
   } 
    int count=0; //convex hull point sayaci
   // Now stack has the output points, print contents of stack 
   while (!S.empty()) 
   { 

       Point p = S.top(); 
       //cout << "(" << p.x << ", " << p.y <<")" << endl; 

       convex_hull_points[count].x = p.x;
       convex_hull_points[count].y = p.y;
        if(count>=1)
       {
       	 convex_hull_lines[count-1].p1.x = convex_hull_points[count-1].x;
       	 convex_hull_lines[count-1].p1.y = convex_hull_points[count-1].y;
       	 convex_hull_lines[count-1].p2.x = convex_hull_points[count].x;
       	 convex_hull_lines[count-1].p2.y = convex_hull_points[count].y;
	   }
    	count++;
       S.pop(); 
   } 
    convex_hull_lines[count-1].p1.x = convex_hull_points[count-1].x;
	convex_hull_lines[count-1].p1.y = convex_hull_points[count-1].y;
	convex_hull_lines[count-1].p2.x = convex_hull_points[0].x;
    convex_hull_lines[count-1].p2.y = convex_hull_points[0].y;
   return count;
} 





void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2);
    if(!point_lock)
    {
	for(int i=0;i<counter;i++)
	{
		glBegin(GL_POINTS);
		glVertex2i(points[i].x, points[i].y);
		glEnd();
	}
	glFlush();
	}
	
}


void OnMouseClick(int button, int state, int x, int y)
{
if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && point_lock==0) 
{ 
 	std::cout<< counter << ".Point  " << x <<" "<<480-y<<std::endl;
 	points[counter].x = x;
  	points[counter].y = 480-y;
  	counter++;
  	
}

}

bool compareInterval(Point_new i1, Point_new i2) 
{ 
    return (i1.a < i2.a); 
} 
 
int t = 11;

bool points_full_stop_check(float stop_p_X[], int index_number)
{
	for(int i = 0;i<index_number;i++)
	{
		if(stop_p_X[i] == 0) 
		{
			return 0;
		}
		else if(i==index_number)
		{
			return 1;
		}
	}
}

void mainMenu2Handler(int choice) {
	
	if((k-1)<3) {
	std::cout<<"polygon point cannot be less than three";
	while(1)
	{
		Sleep(1000);
	}
	}
	
	float x1[100];
	float y1[100];
	float stop_p_X[100]= {0};
	float stop_p_Y[100]= {0};

	for(int i=choice;i<k-1;i++)
	{
		convex_hull_points[i].x = convex_hull_points[i+1].x;
		convex_hull_points[i].y = convex_hull_points[i+1].y;
	}
	k--;
	float vr_X[k];
	float vr_Y[k];
	for(int q =0;q<k;q++)
	{
		vr_X[q]=convex_hull_points[q].x;
		vr_Y[q]=convex_hull_points[q].y;
	}
	
	pair<int, int> ans = find_Centroid(vr_X,vr_Y,k);
	for(int i=0;i<t;i++)
	{
		//glVertex2f(elastic_strip[i].x,elastic_strip[i].y);
		//glVertex2f(320,240);
		elastic_strip_lines[i].p1.x = elastic_strip[i].x;
		elastic_strip_lines[i].p1.y = elastic_strip[i].y;
		elastic_strip_lines[i].p2.x = ans.first;
		elastic_strip_lines[i].p2.y = ans.second;
	}
	
	for(int i=0;i<1000;i++)
	{
	for(int j=0;j<t;j++)
	{
	float slope = (elastic_strip_lines[j].p2.y - elastic_strip_lines[j].p1.y) / (elastic_strip_lines[j].p2.x - elastic_strip_lines[j].p1.x); 
	float ta = atanf(slope);
	x1[j] = elastic_strip_lines[j].p1.x + cos(ta) * i;
	y1[j] = elastic_strip_lines[j].p1.y + sin(ta) * i;
	

	
	
	
	float ds1= distance(elastic_strip_lines[j].p1.x,elastic_strip_lines[j].p1.y,ans.first,ans.second);
	float ds2= distance(x1[j],y1[j],ans.first,ans.second);
	if(ds2>ds1)
	{
		x1[j] = elastic_strip_lines[j].p1.x - cos(ta) * i;
		y1[j] = elastic_strip_lines[j].p1.y - sin(ta) * i;
	}
	
	//polygon icinde mi disinda mi check
	p.x=x1[j];
	p.y=y1[j];

	if(isInside(convex_hull_points, k, p))
	{
		if(stop_p_X[j] == 0)
		{
		stop_p_X[j] = p.x;
		stop_p_Y[j] = p.y;	
		std::cout << "points" << endl;
		std::cout << " Stop" << j << "  " << stop_p_X[j] << "  " << stop_p_Y[j] << endl;
		}
	}
	
	if(stop_p_X[j] != 0 and stop_p_Y[j] != 0)
	{
		x1[j] = stop_p_X[j];
		y1[j] = stop_p_Y[j];
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(int p=0;p<k;p++)
	{
//	std::cout << "convex_hull_points" << endl;
//	std::cout << convex_hull_points[p].x << "  " << convex_hull_points[p].y << endl;
	glBegin(GL_POINTS);
	glVertex2i(convex_hull_points[p].x, convex_hull_points[p].y);
	glEnd();
	}
	
	glColor3f(0.0,1.0,0.0);
	glLineStipple(3, 0xAAAA);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINE_LOOP);
    for(int i=0;i<k;i++)
	{
	glVertex2i(convex_hull_points[i].x, convex_hull_points[i].y);
	}
	glEnd();
	
	glColor3f(1.0,1.0,1.0);	
	glDisable(GL_LINE_STIPPLE);
	glBegin(GL_LINE_LOOP);
	
	for(int k=0;k<t;k++)
	{
		glVertex2f(x1[k],y1[k]);
	}
	glEnd();
	Sleep(5);
	glFlush();	
	}
	if(points_full_stop_check(stop_p_X,t)) break;
	}
	
	glutDestroyMenu(menuID);
	menuID = glutCreateMenu(mainMenu2Handler);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	const char *FirstlistOfOptionText[15];
	FirstlistOfOptionText[0] = "Delete 0.Point";
	FirstlistOfOptionText[1] = "Delete 1.Point";
	FirstlistOfOptionText[2] = "Delete 2.Point";
	FirstlistOfOptionText[3] = "Delete 3.Point";
	FirstlistOfOptionText[4] = "Delete 4.Point";
	FirstlistOfOptionText[5] = "Delete 5.Point";
	FirstlistOfOptionText[6] = "Delete 6.Point";
	for(int i=0;i<k;i++)
	{
		glutAddMenuEntry(FirstlistOfOptionText[i], i);
	}
	
}

void mainMenuHandler(int choice) {
	
	if(choice==0)
	{
		point_lock=1;
		//int n = sizeof(points)/sizeof(points[0]); 
    	k = convexHull(points, counter); 
    	glColor3f(0.0,1.0,0.0);
    	glLineStipple(3, 0xAAAA);
		glEnable(GL_LINE_STIPPLE);
		
    	glBegin(GL_LINE_LOOP);
    	for(int i=0;i<k;i++)
		{
		glVertex2i(convex_hull_points[i].x, convex_hull_points[i].y);
		}
		glEnd();
		glFlush();
	}
	
	
	if(choice==1)
	{
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clean the screen and the depth buffer
	
	elastic_strip[0].x=399; elastic_strip[0].y=425; 
	elastic_strip[1].x=476; elastic_strip[1].y=364; 
	elastic_strip[2].x=520; elastic_strip[2].y=240;
	elastic_strip[3].x=494; elastic_strip[3].y=141;
	elastic_strip[4].x=423; elastic_strip[4].y=68;
	elastic_strip[5].x=294; elastic_strip[5].y=41;
	elastic_strip[6].x=200; elastic_strip[6].y=79;
	elastic_strip[7].x=137; elastic_strip[7].y=159;
	elastic_strip[8].x=126; elastic_strip[8].y=290;
	elastic_strip[9].x=176; elastic_strip[9].y=379;
	elastic_strip[10].x=263; elastic_strip[10].y=431;         

	
	for(int i=0;i<=10;i++)
	{

    	if(i!=10)
    	{
    		elastic_strip_lines[i].p1.x=elastic_strip[i].x;
    		elastic_strip_lines[i].p1.y=elastic_strip[i].y;
    		elastic_strip_lines[i].p2.x=elastic_strip[i+1].x;
    		elastic_strip_lines[i].p2.y=elastic_strip[i+1].y;
		}
	
	}
	elastic_strip_lines[10].p1.x=elastic_strip[10].x;
    elastic_strip_lines[10].p1.y=elastic_strip[10].y;
    elastic_strip_lines[10].p2.x=elastic_strip[0].x;
    elastic_strip_lines[10].p2.y=elastic_strip[0].y;
    
    glDisable(GL_LINE_STIPPLE);
    glColor3f(1.0,1.0,1.0);

	for(int i=0;i<=10;i++)
	{
		glBegin(GL_LINES);
    	glVertex2f(elastic_strip_lines[i].p1.x,elastic_strip_lines[i].p1.y);
    	glVertex2f(elastic_strip_lines[i].p2.x,elastic_strip_lines[i].p2.y);
    	glEnd();
	}
	glFlush();	
	}
	
	if(choice==2)
	{
	for(int p=0;p<k;p++)
	{
	for(int i=0;i<10;i++)
	{
		pdd A = lineFromPoints(elastic_strip_lines[i],convex_hull_points[p]);
		dist[i].perp_x = A.first;
		dist[i].perp_y = A.second;
		dist[i].distance=distance(A.first,A.second,convex_hull_points[p].x,convex_hull_points[p].y);
	}
	float mx = 1000; 
	for(int i=0;i<10;i++)
	{
		mx = min(mx, dist[i].distance); 
	}
	for(int i=0;i<10;i++)
	{
		if(dist[i].distance==mx)
		{
			glColor3f(1.0,0.0,0.0);
			glBegin(GL_LINES);
			glVertex2f(convex_hull_points[p].x,convex_hull_points[p].y);
			glVertex2f(dist[i].perp_x,dist[i].perp_y);
			glEnd();
			elastic_strip[t].x = dist[i].perp_x;
			elastic_strip[t].y = dist[i].perp_y;
			t++;
			break;
		} 
	}
	}
	glFlush();
}


	if(choice==3)
	{	
	

	
	std::cout<< t << endl;
	for(int i=0; i<t; i++){
	sortByAngle[i] = atan2(elastic_strip[i].y - 240, elastic_strip[i].x - 320)* 180 / PI;
    }	
      
    for(int i=0; i<t; i++){

    last_point[i].x = elastic_strip[i].x;
    last_point[i].y = elastic_strip[i].y;
    last_point[i].a = sortByAngle[i];

    }
    

   	sort(last_point, last_point+t, compareInterval); 
   	

   	    
	for(int i=0; i<t; i++){
    elastic_strip[i].x = last_point[i].x;
    elastic_strip[i].y = last_point[i].y;
    std::cout<< i << ".Point" << last_point[i].x<<" "<<last_point[i].y<<" "<< last_point[i].a<<endl;	
	}
	
	float vr_X[100];
	float vr_Y[100];
	for(int q =0;q<k;q++)
	{
		vr_X[q]=convex_hull_points[q].x;
		vr_Y[q]=convex_hull_points[q].y;
	}
	pair<int, int> ans = find_Centroid(vr_X,vr_Y,k);
	//glBegin(GL_LINES); //elastic_strip pointlerinin orta noktaya doðru routes.
	for(int i=0;i<t;i++)
	{
		//glVertex2f(elastic_strip[i].x,elastic_strip[i].y);
		//glVertex2f(320,240);
		elastic_strip_lines[i].p1.x = elastic_strip[i].x;
		elastic_strip_lines[i].p1.y = elastic_strip[i].y;
		elastic_strip_lines[i].p2.x = ans.first;
		elastic_strip_lines[i].p2.y = ans.second;
	}
	//glEnd();
	
//	glBegin(GL_LINES); //elastic_strip pointlerinin orta noktaya doðru routes.
//    for(int i=0;i<k;i++)
//	{
//		glVertex2f(convex_hull_lines[i].p1.x,convex_hull_lines[i].p1.y);
//		glVertex2f(convex_hull_lines[i].p2.x,convex_hull_lines[i].p2.y);
//	}
//	glEnd();
	
	
	
	//linelineintersect
	
	//elastic_strip points ile linelineintersect points distance hesaplama
	
	//enkücük distanceli linelineintersect points ile elastic_strip points arasi route lines
	
float x1[100];
float y1[100];
float stop_p_X[100]= {0};
float stop_p_Y[100]= {0};
	
	for(int i=0;i<1000;i++)
	{
	for(int j=0;j<t;j++)
	{

	//faha önceden polygon a takilmis point varsa durdur

	
	float slope = (elastic_strip_lines[j].p2.y - elastic_strip_lines[j].p1.y) / (elastic_strip_lines[j].p2.x - elastic_strip_lines[j].p1.x); 
	float ta = atanf(slope);
	x1[j] = elastic_strip_lines[j].p1.x + cos(ta) * i;
	y1[j] = elastic_strip_lines[j].p1.y + sin(ta) * i;
	float ds1= distance(elastic_strip_lines[j].p1.x,elastic_strip_lines[j].p1.y,ans.first,ans.second);
	float ds2= distance(x1[j],y1[j],ans.first,ans.second);
	if(ds2>ds1)
	{
		x1[j] = elastic_strip_lines[j].p1.x - cos(ta) * i;
		y1[j] = elastic_strip_lines[j].p1.y - sin(ta) * i;
	}
	
	//polygon icinde mi disinda mi check
	p.x=x1[j];
	p.y=y1[j];

	if(isInside(convex_hull_points, k, p))
	{
		if(stop_p_X[j] == 0)
		{
		stop_p_X[j] = p.x;
		stop_p_Y[j] = p.y;	
		std::cout << "points" << endl;
		std::cout << " Stop" << j << "  " << stop_p_X[j] << "  " << stop_p_Y[j] << endl;
		}
	}
	
	if(stop_p_X[j] != 0 and stop_p_Y[j] != 0)
	{
		x1[j] = stop_p_X[j];
		y1[j] = stop_p_Y[j];
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(int p=0;p<k;p++)
	{
//	std::cout << "convex_hull_points" << endl;
//	std::cout << convex_hull_points[p].x << "  " << convex_hull_points[p].y << endl;
	glBegin(GL_POINTS);
	glVertex2i(convex_hull_points[p].x, convex_hull_points[p].y);
	glEnd();
	}
	
	glColor3f(0.0,1.0,0.0);
	glLineStipple(3, 0xAAAA);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINE_LOOP);
    for(int i=0;i<k;i++)
	{
	glVertex2i(convex_hull_points[i].x, convex_hull_points[i].y);
	}
	glEnd();
	
	glColor3f(1.0,1.0,1.0);	
	glDisable(GL_LINE_STIPPLE);
	glBegin(GL_LINE_LOOP);
	
	for(int k=0;k<t;k++)
	{
		glVertex2f(x1[k],y1[k]);
	}
	glEnd();
	
	Sleep(5);
	glFlush();	
	}
	if(points_full_stop_check(stop_p_X,t)) break;
	}
	
	
	
	Sleep(100);
	glutDestroyMenu(menuID);
	menuID = glutCreateMenu(mainMenu2Handler);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	const char *FirstlistOfOptionText[15];
	FirstlistOfOptionText[0] = "Delete 0.Point";
	FirstlistOfOptionText[1] = "Delete 1.Point";
	FirstlistOfOptionText[2] = "Delete 2.Point";
	FirstlistOfOptionText[3] = "Delete 3.Point";
	FirstlistOfOptionText[4] = "Delete 4.Point";
	FirstlistOfOptionText[5] = "Delete 5.Point";
	FirstlistOfOptionText[6] = "Delete 6.Point";
	FirstlistOfOptionText[7] = "Delete 7.Point";
	FirstlistOfOptionText[8] = "Delete 8.Point";
	FirstlistOfOptionText[9] = "Delete 9.Point";
	FirstlistOfOptionText[10] = "Delete 10.Point";
	for(int i=0;i<k;i++)
	{
		glutAddMenuEntry(FirstlistOfOptionText[i], i);
	}
	
	
	}


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

	
	menuID = glutCreateMenu(mainMenuHandler);
	glutAddMenuEntry("convex hull calc", 0);
	glutAddMenuEntry("draw elastic_strip", 1);
	glutAddMenuEntry("find new elastic_strip edges", 2);
	glutAddMenuEntry("start animation", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}


