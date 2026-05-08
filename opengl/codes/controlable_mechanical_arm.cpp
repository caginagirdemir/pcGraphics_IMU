
#include <GL/glut.h>

static int shoulder_z,shoulder_y,shoulder_x = 0, elbow_z,elbow_y,elbow_x = 0, head_z,head_y,head_x = 0;
GLfloat _x, _y, spin_x = 0, spin_y = 0;


void wireBox(GLdouble width, GLdouble height, GLdouble depth) {
  glPushMatrix();
  glScalef(width, height, depth);
  glutWireCube(1.0);
  glPopMatrix();
}


void display() {

  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
    glRotatef(spin_x, 0, 1, 0);
    glRotatef(spin_y, 1, 0, 0);

  glRotatef((GLfloat)shoulder_z, 0.0, 0.0, 1.0);
  glRotatef((GLfloat)shoulder_y, 0.0, 1.0, 0.0);
  glRotatef((GLfloat)shoulder_x, 1.0, 0.0, 0.0);
  wireBox(2.0, 1, 1.0);

  glTranslatef(1.0, 0.0, 0.0);
  glRotatef((GLfloat)elbow_z, 0.0, 0.0, 1.0);
  glRotatef((GLfloat)elbow_y, 0.0, 1.0, 0.0);
  glRotatef((GLfloat)elbow_x, 1.0, 0.0, 0.0);
  glTranslatef(1.0, 0.0, 0.0);
  wireBox(2.0, 1, 1.0);
  
  glTranslatef(1.0, 0.0, 0.0);
  glRotatef((GLfloat)head_z, 0.0, 0.0, 1.0);
  glRotatef((GLfloat)head_y, 0.0, 1.0, 0.0);
  glRotatef((GLfloat)head_x, 1.0, 0.0, 0.0);
glBegin(GL_LINE_STRIP);
glVertex3f(.6,.9,.9);
glVertex3f(0,.5,.5);
glVertex3f(0,.5,-.5);
glVertex3f(.6,.9,-.9);
glVertex3f(.6,.9,.9);
  glEnd();
  
glBegin(GL_LINE_STRIP);
glVertex3f(.6,.9,.9);
glVertex3f(0,.5,.5);
glVertex3f(0,-.5,.5);
glVertex3f(.6,-.9,.9);
glVertex3f(.6,.9,.9);
  glEnd();
 glBegin(GL_LINE_STRIP);
glVertex3f(.6,-.9,.9);
glVertex3f(0,-.5,.5);
glVertex3f(0,-.5,-.5);
glVertex3f(.6,-.9,-.9);
glVertex3f(.6,-.9,.9);
  glEnd();
  
   glBegin(GL_LINE_STRIP);
glVertex3f(.6,.9,-.9);
glVertex3f(0,.5,-.5);
glVertex3f(0,-.5,-.5);
glVertex3f(.6,-.9,-.9);
glVertex3f(.6,.9,-.9);
  glEnd();
    glTranslatef(1.0, 0.0, 0.0);
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
  gluLookAt(1,2,8, 0,0,0, 0,1,0);
}
void mouse(int button, int state, int x, int y)
{
    spin_x = x;
    spin_y = y;

    glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y)
{
  
  
//shoulder kontrol seti
switch(key) {
    case 'a' : (shoulder_z -= 5) %= 360; glutPostRedisplay(); break;
    case 's' : (shoulder_z += 5) %= 360; glutPostRedisplay(); break;
    case 'd' : (shoulder_x -= 5) %= 360; glutPostRedisplay(); break;
    case 'f' : (shoulder_x += 5) %= 360; glutPostRedisplay(); break;
    case 'g' : (shoulder_y -= 5) %= 360; glutPostRedisplay(); break;
    case 'h' : (shoulder_y += 5) %= 360; glutPostRedisplay(); break;
}
  
  
//elbow kontrol seti
switch(key) {
    case 'z' : (elbow_z -= 5) %= 360; glutPostRedisplay(); break;
    case 'x' : (elbow_z += 5) %= 360; glutPostRedisplay(); break;
    case 'c' : (elbow_x -= 5) %= 360; glutPostRedisplay(); break;
    case 'v' : (elbow_x += 5) %= 360; glutPostRedisplay(); break;
    case 'b' : (elbow_y -= 5) %= 360; glutPostRedisplay(); break;
    case 'n' : (elbow_y += 5) %= 360; glutPostRedisplay(); break;
}

//head kontrol seti
switch(key) {
    case 'q' : (head_z -= 5) %= 360; glutPostRedisplay(); break;
    case 'w' : (head_z += 5) %= 360; glutPostRedisplay(); break;
    case 'e' : (head_x -= 5) %= 360; glutPostRedisplay(); break;
    case 'r' : (head_x += 5) %= 360; glutPostRedisplay(); break;
    case 't' : (head_y -= 5) %= 360; glutPostRedisplay(); break;
    case 'y' : (head_y += 5) %= 360; glutPostRedisplay(); break;
}

}
void motion(int x, int y)
{
    spin_x = x - _x;
    spin_y = y - _y;

    glutPostRedisplay();
}
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(800, 600);
  glutCreateWindow("soru3");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
      glutMotionFunc(motion);
    glutMouseFunc(mouse);
  init();
  glutMainLoop();
}
