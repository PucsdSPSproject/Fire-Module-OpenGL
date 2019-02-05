#include"delay.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <GL/glut.h>
#include<stdio.h>
void init(void);
void display(void);
void reshape(int w, int h);

GLfloat ctrlpoints[9][3] = {
	{4.0, 0.0,0.0}, { 4.0, 4.0,0.0}, 
	{0.0, 4.0,0.0}, {-4.0,4.0,0.0},{-4.0, 0.0,0.0},{-4.0, -4.0,0.0},{0.0, -4.0,0.0},{4.0,-4.0,0.0},{4.0, 0.0,0.0}};
int flag=1;
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
}

void display(void)
{
	int i,j;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 9, &ctrlpoints[0][0]);
	glEnable(GL_MAP1_VERTEX_3);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i <=50; i++) 
		glEvalCoord1f((GLfloat) i/50);
	glEnd();
	glPointSize(5.0);
	glColor3f(1.0, 1.0, 1.0);
	
	glBegin(GL_POINTS);
		
	for (i = 0; i < 9; i++) 
	{
		glVertex3fv(&ctrlpoints[i][0]);
						
	}
	if(flag==1)
	{
	for(i=0;i<9;i++)
	{
		for(j=0;j<2;j++)
		{
			if(j==0)
			{
				if(i==0 || i==8)
					ctrlpoints[i][j]+=(GLfloat)0.05;
				else if( i==4)
					ctrlpoints[i][j]-=(GLfloat)0.1;
				
			}
			if(j==1)
			{
				if(i==2)
					ctrlpoints[i][j]+=(GLfloat)0.1;
				else if(i==6)
					ctrlpoints[i][j]-=(GLfloat)0.1;
			}
			if(i==1)
				ctrlpoints[i][j]-=(GLfloat)0.1;
			
			if(i==3)
			{
				if(j==0)
					ctrlpoints[i][j]+=(GLfloat)0.1;
				if(j==1)
					ctrlpoints[i][j]-=(GLfloat)0.1;
			}
			if(i==5)
				ctrlpoints[i][j]+=(GLfloat)0.1;
			if(i==7)
			{
				if(j==0)
					ctrlpoints[i][j]-=(GLfloat)0.1;
				if(j==1)
					ctrlpoints[i][j]+=(GLfloat)0.1;
			}
			
				
				
			if(ctrlpoints[2][1]>=5)
				flag=0;
		}
	
	}
	}
	else if(flag==0)
	{
	for(i=0;i<9;i++)
	{
		for(j=0;j<2;j++)
		{
			if(j==0)
			{
				if(i==0 || i==8)
					ctrlpoints[i][j]-=(GLfloat)0.05;
				else if( i==4)
					ctrlpoints[i][j]+=(GLfloat)0.1;
			}
			if(j==1)
			{
				if(i==2)
					ctrlpoints[i][j]-=(GLfloat)0.1;
				else if(i==6)
					ctrlpoints[i][j]+=(GLfloat)0.1;
			}
			if(i==1)
				ctrlpoints[i][j]+=(GLfloat)0.1;
			
			if(i==3)
			{
				if(j==0)
					ctrlpoints[i][j]-=(GLfloat)0.1;
				if(j==1)
					ctrlpoints[i][j]+=(GLfloat)0.1;
			}
			if(i==5)
				ctrlpoints[i][j]-=(GLfloat)0.1;
			if(i==7)
			{
				if(j==0)
					ctrlpoints[i][j]+=(GLfloat)0.1;
				if(j==1)
					ctrlpoints[i][j]-=(GLfloat)0.1;
			}
			if(ctrlpoints[2][1]<=4)
				flag=1;
		}
	
	}
	}
		
		
	glEnd();
	delay(0.3);
	glutSwapBuffers();
	glutPostRedisplay();
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-5.0, 5.0, -5.0*(GLfloat)h/(GLfloat)w,5.0*(GLfloat)h/(GLfloat)w, -5.0, 5.0);
	else
		glOrtho(-5.0*(GLfloat)w/(GLfloat)h,5.0*(GLfloat)w/(GLfloat)h, -5.0, 5.0, -5.0, 5.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (700, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
 	
