#include <GL/glut.h>
#include <iostream>
#include "bits/stdc++.h" 
#include <math.h>   
#define PI 3.14 
using namespace std;

struct Colors {
   int x_, y_, E_;
};

static int shoulder_z,shoulder_y,shoulder_x = 0, elbow_z,elbow_y,elbow_x = 0, head_z,head_y,head_x = 0;
GLfloat _x, _y, spin_x = 0, spin_y = 0;
float plane_size_X,plane_size_Y,angle_x[4],angle_y[4],plane_depth[4],blub_type[4],blub_watt[4],blub_lumen[4];
int count_1, source_flag = 0;
bool calc_flag,calc_flag_2;
bool orbit_flag=1;
float red[3],green[3],blue[3];
int __x,__y=0;
float w2_x,w2_y=0;
float _w2_x,_w2_y,w2_sc2_x,w2_sc2_y = 0;
bool window2_click_flag = 0;
float screen2[500][500] = {0};
bool plot_flag=0;
int X_,Y_=0;
int place_choose,lux_value,lux_factor=0;
bool ref_screen_flag=0;
int Screen_no=0;
float I_reflection;

void wireBox(GLdouble width, GLdouble height, GLdouble depth) {
  glPushMatrix();
  glScalef(width, height, depth);
  glutWireCube(1.0);
  glPopMatrix();
}

int dotProduct(int vect_A[], int vect_B[]) 
{ 
  
    int product = 0; 
  
    // Loop for calculate cot product 
    for (int i = 0; i < 3; i++) 
  
        product = product + vect_A[i] * vect_B[i]; 
    return product; 
} 

float calculateAngle( 
    float x1, float y1, float z1, 
    float x2, float y2, float z2, 
    float x3, float y3, float z3) 
{ 
    // Find direction ratio of line AB 
    float ABx = x1 - x2; 
    float ABy = y1 - y2; 
    float ABz = z1 - z2; 
  
    // Find direction ratio of line BC 
    float BCx = x3 - x2; 
    float BCy = y3 - y2; 
    float BCz = z3 - z2; 
  
    // Find the dotProduct 
    // of lines AB & BC 
    double dotProduct 
        = ABx * BCx 
          + ABy * BCy 
          + ABz * BCz; 
  
    // Find magnitude of 
    // line AB and BC 
    double magnitudeAB 
        = ABx * ABx 
          + ABy * ABy 
          + ABz * ABz; 
    double magnitudeBC 
        = BCx * BCx 
          + BCy * BCy 
          + BCz * BCz; 
  
    // Find the cosine of 
    // the angle formed 
    // by line AB and BC 
    double angle = dotProduct; 
    angle /= sqrt( 
        magnitudeAB * magnitudeBC); 
  
    // Find angle in radian 
    angle = (angle * 180) / PI; 
  
    // Print the angle 
    return abs(angle); 
} 

float distance(float x1, float y1,  
            float z1, float x2,  
            float y2, float z2) 
{ 
    float d = sqrt(pow(x2 - x1, 2) +  
                pow(y2 - y1, 2) +  
                pow(z2 - z1, 2) * 1.0); 
    std::cout << std::fixed; 
    std::cout << std::setprecision(2); 
    return d; 
} 


void display() {


	
  	glClear(GL_COLOR_BUFFER_BIT);
  	glMatrixMode(GL_MODELVIEW);
  	glPushMatrix(); 
	glRotatef(spin_x, 0, 1, 0);
	glRotatef(spin_y, 1, 0, 0);
	
	
	wireBox(plane_size_X,plane_size_Y,0); //plane 1 draw
	
	glRotatef(90, 1, 0, 0); //plane 2 location adjustment *

	glTranslatef(0.0, 3.0, 0);
  	glTranslatef(0, 0.0, 0.0);
  	glTranslatef(0.0, 0, -3.0);
  	glPushMatrix();
  	wireBox(plane_size_X,plane_size_Y,0); //plane 2 draw
	glPopMatrix();

	for(int i=0;i<count_1;i++)
	{
	if(count_1>=1) //if adding two or more light source, to reset location setting
	{
		glTranslatef(0.0, 0.0, -1*plane_depth[i-1]);
  		glTranslatef(-1*angle_x[i-1], 0.0, 0.0);
  		glTranslatef(0.0, -1*angle_y[i-1], 0.0);
	}
	
  	glTranslatef(0.0, 0.0, plane_depth[i]); //location values from entered by user
  	glTranslatef(angle_x[i], 0.0, 0.0);
  	glTranslatef(0.0, angle_y[i], 0.0);
	
	glutWireSphere(.2, 5, 5); //light source sphere for visuality
	           
	glColor3f(1.0,0.0,0.0);

	glBegin(GL_LINES); //line draw between light source and base
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(0.0,0.0,-1*plane_depth[i]);
	glEnd();

	if(window2_click_flag) //if click on screen 2
	{
		if(_w2_x!=w2_x) //if clicked point is same, don't again calculations
		{
			cout<< w2_x<< "  " << w2_y <<endl; 
		}

		glBegin(GL_LINES); //line draw between light source amd click point by user
		glVertex3f(0.0,0.0,0.0);
		glVertex3f((-1*angle_x[i])-(plane_size_X/2)+w2_x,(-1*angle_y[i])-(plane_size_Y/2)+w2_y,-1*plane_depth[i]);
		glEnd();
		
	
  	glPushMatrix(); //adjustments to draw dot on plane 2
  	
  	glTranslatef(0.0, 0.0, -1*plane_depth[i]); // to restore location settings
  	glTranslatef(-1*angle_x[i], 0.0, 0.0);
  	glTranslatef(0.0, -1*angle_y[i], 0.0);
  	
	glRotatef(90, 1, 0, 0); //plane 2 location adjustment * again
	glTranslatef(0.0, 3.0, 0);
  	glTranslatef(0, 0.0, 0.0);
  	glTranslatef(0.0, 0, 3.0);

  	glPointSize(10);
  	
  	glLineWidth(2);
  	glColor3f(0.0,1.0,0.0);
	glLineStipple(3, 0xAAAA);
	glEnable(GL_LINE_STIPPLE);
  	glBegin(GL_LINES);
  	if(Screen_no == 0)
	{
		glVertex3f(0,0,0); //draw point between plane 2 point and light source
	}
	else
	{
		glVertex3f((plane_size_X/2)-w2_sc2_x,plane_size_Y-(plane_size_Y/2)-w2_sc2_y,0); //if the second screen was cliked, set to selected point by user
	}
	glVertex3f(0+angle_x[i],3-(6-plane_depth[i]),-3-angle_y[i]);
  	glEnd();
  	glLineWidth(1);
  	glDisable(GL_LINE_STIPPLE);
  	glColor3f(1.0,0.0,0.0);
  	
  	glLineWidth(2);
  	glColor3f(0.0,1.0,1.0);
	glLineStipple(3, 0xAAAA);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES); //this time, line draw between plane 2 point and selected point by user on plane 1
	if(Screen_no == 0)
	{
		glVertex3f(0,0,0); //if the second screen was never cliked, set to mid point
	}
	else
	{
		glVertex3f((plane_size_X/2)-w2_sc2_x,plane_size_Y-(plane_size_Y/2)-w2_sc2_y,0); //if the second screen was cliked, set to selected point by user
	}
	glVertex3f(0-(plane_size_X/2)+w2_x,-3,-3+(plane_size_Y/2)-w2_y);
	glEnd();
	glLineWidth(1);
  	glDisable(GL_LINE_STIPPLE);
  	glColor3f(1.0,0.0,0.0);
	
	glBegin(GL_POINTS); //put point selected point by user on plane 2
	if(Screen_no == 0)
	{
		glVertex3f(0,0,0);//if the second screen was never cliked, set to mid point
	}
	else
	{
		glVertex3f((plane_size_X/2)-w2_sc2_x,plane_size_Y-(plane_size_Y/2)-w2_sc2_y,0); //if the second screen was cliked, set to selected point by user
	}
	glEnd();
	
	glPopMatrix(); //remove stack
	
	

	// distance, angles, lumen, illuminance calculations
		
		glColor3f(1.0,1.0,1.0);
		glPointSize(10);
		float x1=0.0; 
		float y1=0.0; 
		float z1=-1*plane_depth[i]; 
		
		float x2=0.0; 
		float y2=0.0; 
		float z2=0.0; 
		
		float x3=(-1*angle_x[i])-(plane_size_X/2)+w2_x; 
		float y3=(-1*angle_y[i])-(plane_size_Y/2)+w2_y; 
		float z3=-1*plane_depth[i];
		
		glBegin(GL_POINTS); 
		glVertex3f(x1,y1,z1);
		glVertex3f(x2,y2,z2);
		glVertex3f(x3,y3,z3);
		glEnd();   		



	float angle = calculateAngle(x1, y1, z1, x2, y2, z2, x3, y3, z3);
	
	float d =distance(0,0,0,x3,y3,z3);
	float d1 =distance(x1,y1,z1,x3,y3,z3);
	float d2 =plane_depth[i];

	float degree = atan(d1/d2);
	float degree2 = cos(degree);
	
	float d_2 =distance(0,0,0,(plane_size_X/2)-w2_sc2_x,plane_size_Y-(plane_size_Y/2)-w2_sc2_y,0);
	float d_2_1 =distance(0,0,0,(plane_size_X/2)-w2_sc2_x,plane_size_Y-(plane_size_Y/2)-w2_sc2_y,0);
	float d_2_2 =distance((plane_size_X/2)-w2_sc2_x,plane_size_Y-(plane_size_Y/2)-w2_sc2_y,0,    (-1*angle_x[i])-(plane_size_X/2)+w2_x,(-1*angle_y[i])-(plane_size_Y/2)+w2_y,-1*plane_depth[i]);

	float degree_3 = atan(d_2_1/d_2_2);
	float degree3 = cos(degree_3);

	int A[] = { x2-x1, y2-y1, z2-z1 }; 
    int C[] = { x2-x3, y2-y3, z2-z3 }; 
    
	float I_reflection = 0.1*blub_lumen[i]*dotProduct(A,C); //printing on consele I_diff(luminous value, lumen unit) comes from each light source in loop

	float E=(blub_lumen[i]*degree2)/(d*d); //printing on console E(illimunance value, lux unit) comes from each light source in loop

	if(_w2_x!=w2_x) //if point wasn't change, not print on console
	{
	cout<< i << ".source contribition (Lux)" << E <<endl;
	cout<< " Point Reflection (Lumen)" << I_reflection<<endl;
	}
	_w2_x = w2_x;
	
	
	float E_sum=E_sum+(E+I_reflection*degree3)/(d_2*d_2));
	
	
	}
	else //If a dot is not selected on the 2d screen, line draw between light source and the base
	{
	glBegin(GL_LINES); 
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(-1*angle_x[i],-1*angle_y[i],-1*plane_depth[i]);
	glEnd();
	}
	
	//draw line x,y,z axis for visuality
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(1.0,0.0,0.0);
	glEnd();
	glFlush();
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(0.0,1.0,0.0);
	glEnd();
	glColor3f(1.0,1.0,1.0);
	
	float t;
	if(calc_flag !=1)
	{


    }
    if(calc_flag)
  	{
  	

		for(float r=0.00;r<plane_size_X;r+=0.01)
		{
		for(float e=0.00;e<plane_size_Y;e+=0.01)
		{

		
		float d_ =distance(0,0,0,((-1*angle_x[i])-(plane_size_X/2))+r,((-1*angle_y[i])-(plane_size_Y/2))+e,-1*plane_depth[i]);
		
		float d_1 =distance(0.0,0.0,-1*plane_depth[i],((-1*angle_x[i])-(plane_size_X/2))+r,((-1*angle_y[i])-(plane_size_Y/2))+e,-1*plane_depth[i]);
		
		float d_2 =plane_depth[i];
		
		float degree = atan(d_1/d_2);
		float degree2 = cos(degree);
		float results = (450*degree2)/(d_*d_);
		X_=r*100;
		Y_=e*100;
		
		if(i == 0)
		{
		screen2[X_][Y_] = results;
		}
		else
		{
		screen2[X_][Y_] += results;
		}
		}
		}

	}
	}


glColor3f(1.0,1.0,1.0);
  	glPopMatrix();
  	glFlush();
	}


void reshape(GLint w, GLint h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, GLfloat(w)/GLfloat(h), 1.0, 20.0);
}

void init() {
  glShadeModel(GL_FLAT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(1,2,15, 0,0,0, 0,1,0);
          glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0.0,0.0,0.0,0.0);
}
void mouse(int button, int state, int x, int y)
{
if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
{
if(Screen_no == 0) // windows 2 menu selected that clickable to plane 1
{
_w2_x = w2_x;
_w2_y = w2_y;
w2_x =plane_size_X-((plane_size_X*100 - x)/100);
w2_y =(plane_size_Y*100 - y)/100;
    window2_click_flag=1;	
}
else if(Screen_no == 1) // windows 2 menu selected that clickable to plane 2
{
	w2_sc2_x =plane_size_X-((plane_size_X*100 - x)/100);
	w2_sc2_y =(plane_size_Y*100 - y)/100;
}

}
}


void mainMenuHandler(int choice) {
	
	if(choice == 0)
	{
		
	red[count_1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	green[count_1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	blue[count_1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	
	std::cout<<"dimession between plane to light source"<<endl;
	std::cin>>plane_depth[count_1];
  	std::cout<<"Please enter "<<endl;
  	std::cout<<"1.Standart | ";
  	std::cout<<"2.Halogen | ";
  	std::cout<<"3.CFL | ";
  	std::cout<<"4.LED" << endl;
  	std::cin>>blub_type[count_1];
  	std::cout<<"--40W-------29W------9W----6W--"<<endl;
  	std::cout<<"--60W-------42W------14W----9W--"<<endl;
  	std::cout<<"--75W-------53W------18W----11W--"<<endl;
  	std::cout<<"--100W------72W------23W----14W--"<<endl;
	
  	std::cin>>blub_watt[count_1];
  	if(blub_type[count_1]==1)
	{
	  	if(blub_watt[count_1]==40) blub_lumen[count_1] =450;	
	  	if(blub_watt[count_1]==60) blub_lumen[count_1] =800;
	  	if(blub_watt[count_1]==75) blub_lumen[count_1] =1100;
	  	if(blub_watt[count_1]==100) blub_lumen[count_1] =1600;
	} 
	else if(blub_type[count_1]==2)
	{
	  	if(blub_watt[count_1]==29) blub_lumen[count_1] =450;	
	  	if(blub_watt[count_1]==42) blub_lumen[count_1] =800;
	  	if(blub_watt[count_1]==53) blub_lumen[count_1] =1100;
	  	if(blub_watt[count_1]==72) blub_lumen[count_1] =1600;
	} 
		else if(blub_type[count_1]==3)
	{
	  	if(blub_watt[count_1]==9) blub_lumen[count_1] =450;	
	  	if(blub_watt[count_1]==14) blub_lumen[count_1] =800;
	  	if(blub_watt[count_1]==18) blub_lumen[count_1] =1100;
	  	if(blub_watt[count_1]==23) blub_lumen[count_1] =1600;
	} 
		else if(blub_type[count_1]==4)
	{
	  	if(blub_watt[count_1]==6) blub_lumen[count_1] =450;	
	  	if(blub_watt[count_1]==9) blub_lumen[count_1] =800;
	  	if(blub_watt[count_1]==11) blub_lumen[count_1] =1100;
	  	if(blub_watt[count_1]==14) blub_lumen[count_1] =1600;
	} else
	{
		std::cout << "invalid input" << endl;
	}
  	
  	  	
	std::cout<<"Angle_x"<<endl;
  	std::cin>>angle_x[count_1];
  	std::cout<<"Angle_y"<<endl;
  	std::cin>>angle_y[count_1];
	source_flag = 1;
	
	count_1++;

	}
	else if(choice == 1)
	{
		

	
calc_flag=1;
display();
}

}

void motion(int x, int y)
{
    spin_x = x - _x;
    spin_y = y - _y;

    glutPostRedisplay();
}

void passive(int x1,int y1) {
    __x=x1; __y=y1;
}

void mainMenuHandler2(int choice) {

	if(choice) Screen_no=1;
	else Screen_no=0;
}


void drawScene2()
{
	
	if(!ref_screen_flag)
	{

	glColor3f(1.0,1.0,1.0);
	float t;
	
	for (int i=1;i<5;i++)
	{
    glBegin(GL_LINE_LOOP);
    for (int p=0;p<360;p++)
    {
        t=p*3.142/180;
        glVertex2f((plane_size_X*100)/2+i*50*cos(t),(plane_size_Y*100)/2+i*50*sin(t));
    }
    glEnd();
	}
	
	glBegin(GL_LINES);
	glVertex2f(plane_size_X*100/2,0);
	glVertex2f(plane_size_X*100/2,plane_size_Y*100);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex2f(0,plane_size_Y*100/2);
	glVertex2f(plane_size_X*100,plane_size_Y*100/2);
	glEnd();

	if(calc_flag)
  	{
  	if(plot_flag == 0)
  	{

  	cout << "1-Lunch & Break Room" << endl;
  	cout << "2-Classroom (for Challenging)" << endl;
  	cout << "3-Classroom (Typical Application)" << endl;
  	cout << "4-Open Office (Desk)" << endl;
  	cin >> place_choose;
  	
  	if(place_choose)  lux_value=50; lux_factor=5;
  	if(place_choose==2)  lux_value=269; lux_factor=20;
  	if(place_choose==3)  lux_value=162; lux_factor=10;
  	if(place_choose==4)  lux_value=323; lux_factor=15;
  	
  	cout << "Red - " << lux_value << " to Yellow - " << lux_value << " every color transition " << lux_factor << " lux value";
  	}
  	
  	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  	glClearColor(0.0,0.0,0.0,0.0);
  	glColor3f(0.0,0.0,0.0); 	

	for(int r=0;r<plane_size_X*100;r+=1)
	{
	for(int e=0;e<plane_size_Y*100;e+=1)
	{
	glPointSize(1);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_POINTS);


	if(screen2[r][e]>lux_value)
	{
		glColor3f(1.0,0.0,0.0); 
	}
	else if(screen2[r][e]>lux_value-lux_factor)
	{
		glColor3f(1,.1,0.0); 
	}
	else if(screen2[r][e]>lux_value-lux_factor*2)
	{
		glColor3f(1,.2,0.0); 
	}
	else if(screen2[r][e]>lux_value-lux_factor*3)
	{
		glColor3f(1,.3,0.0); 
	}
	else if(screen2[r][e]>lux_value-lux_factor*4)
	{
		glColor3f(1,.4,0.0); 
	}
	else if(screen2[r][e]>lux_value-lux_factor*5)
	{
		glColor3f(1,.5,0.0); 
	}
	else if(screen2[r][e]>lux_value-lux_factor*6)
	{
		glColor3f(1,.6,0.0); 
	}
	else if(screen2[r][e]>lux_value-lux_factor*7)
	{
		glColor3f(1,.7,0.0); 
	}
	else if(screen2[r][e]>lux_value)
	{
		glColor3f(1,.8,0.0); 
	}
	else if(screen2[r][e]>lux_value)
	{
		glColor3f(1,.9,0.0); 
	}
	else if(screen2[r][e]>lux_value)
	{
		glColor3f(1,1,0.0); 
	}
	else if(screen2[r][e]>0)
	{
		glColor3f(0,1,0.0); 
	}
	
	glVertex2f(r,e);
	glEnd();
	
	
	glColor3f(0.0,1.0,0.0); 
	}

  	}
  	plot_flag=1;
	}

    glFlush();
	}	
}

int main(int argc, char** argv) {
	
	std::cout<<"Welcome to light effect simulation engine with OpenGL"<<endl;
  	std::cout<<"plane x axis value"<<endl;
  	std::cin>>plane_size_X;
  	std::cout<<"plane y axis value"<<endl;
  	std::cin>>plane_size_Y;
  	



  	
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(800, 600);
  
  //window 1
  glutCreateWindow("CMP715 Project");
  glutDisplayFunc(display);
glutReshapeFunc(reshape);
//	glutKeyboardFunc(keyboard);
    glutMotionFunc(motion);
    glutCreateMenu(mainMenuHandler);
	glutAddMenuEntry("add light source", 0);
	glutAddMenuEntry("plot", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
//    glutMouseFunc(mouse);
    glutPassiveMotionFunc(passive);
    init();
    
    glutInitWindowSize(plane_size_X*100, plane_size_Y*100); 
    glutCreateWindow("Window2");
    glutPositionWindow(80,60);
    glutDisplayFunc(drawScene2);
    glutMouseFunc(mouse);
    glutCreateMenu(mainMenuHandler2);
	glutAddMenuEntry("reflection screen off", 0);
	glutAddMenuEntry("reflection screen on", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, plane_size_X*100, 0, plane_size_Y*100);
	

  glutMainLoop();
}
