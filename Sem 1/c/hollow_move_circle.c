#include"delay.h"
#include<math.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#define PI 3.1452423
float color=0.0f;
int flag=0;

void myinit(void);
void myDisplay(void);

void myinit(void)
{
	glClearColor(1.0,1.0,1.0,1.0);
}

void myDisplay(void)
{
	GLint number=20,i;
	GLdouble radius=0.4f,twoPi=2.0*PI;
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glScalef(color,color,color);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.9f,color,0.0f);	
	for(i=1;i<=25;i++)
		glVertex2d(radius*cos(i*twoPi/number),radius*sin(i*twoPi/number));
	glEnd();
	if(color<1.0 && flag==0)
	{
		color=color+0.01f;
		if(color>1.0) flag=1;
	}
	else if(flag==1)	
	{	
		color=color-0.01f;
		if(color<0) flag=0;
	}

	glPopMatrix();
	glutSwapBuffers();
	glutPostRedisplay();
	delay(rand()%10/100.0);
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
	myinit();
	glutMainLoop();
	return 0;
}
