#include <math.h>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;
#define pdd pair<double, double>

struct Point_new {
   float x, y, a;
};

pdd points[240];
Point_new last_point[240];
float sortByAngle[240];
int counter = 15;
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



int main()
{
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
    	
    	for(int i=0; i<counter; i++){
		std::cout << i << "  " << last_point[i].x << "  "<< last_point[i].y << "  " << last_point[i].a << std::endl;
	  	}
}
