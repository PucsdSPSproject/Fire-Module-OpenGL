#include "delay.h"
#include<math.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#define PI 3.1452423

void myDisplay(void);
void myDisplay(void)
{
	int i;
	int number=40;
	double radius=0.4f,twoPi=2.0*PI;
	
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	
	glBegin(GL_POLYGON);
	glColor3f(0.9f,0.1f,0.0f);	
	for(i=1;i<=40;i++)
		glVertex3d(radius*cos(i*twoPi/number),radius*sin(i*twoPi/number),0.4f);
	glEnd();
	
	glPopMatrix();
	glutSwapBuffers();
	glutPostRedisplay();
	
	glFlush();
}
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(700,700);
	glutInitWindowPosition(600,600);
	glutCreateWindow("OpenGL");
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
