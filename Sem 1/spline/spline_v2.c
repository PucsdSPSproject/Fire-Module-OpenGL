#include"delay.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <GL/glut.h>
#include<stdio.h>
void init(void);
void display(void);
void reshape(int w, int h);


void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
}

void display(void)
{
	int i,k;
	GLfloat ctrlpoints[8][3][3] = {{{40.0, 0.0,0.0}, {40.0,15.0,0.0},{30.0, 30.0,0.0}},
				       {{30.0, 30.0,0.0}, {15.0,40.0,0.0},{0.0, 40.0,0.0}},
				       {{0.0, 40.0,0.0}, {-15.0,40.0,0.0},{-30.0, 30.0,0.0}},
				       {{-30.0, 30.0,0.0}, {-40.0,15.0,0.0},{-40.0, 0.0,0.0}},
				       {{-40.0, 0.0,0.0}, {-40.0,-15.0,0.0},{-30.0, -30.0,0.0}},
				       {{-30.0, -30.0,0.0}, {-15.0,-40.0,0.0},{0.0, -40.0,0.0}},
				       {{0.0, -40.0,0.0}, {15.0,-40.0,0.0},{30.0, -30.0,0.0}},
				       {{30.0, -30.0,0.0}, {40.0,-15.0,0.0},{40.0, 0.0,0.0}}};
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();
	for(k=0;k<8;k++)
	{
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 3, &ctrlpoints[k][0][0]);
		glEnable(GL_MAP1_VERTEX_3);
		glBegin(GL_LINE_STRIP);
		for (i = 0; i <= 50; i++) 
			glEvalCoord1f((GLfloat) i/50);
		glEnd();
		glPointSize(5.0);
		glColor3f(1.0, 1.0, 1.0);
		
		glBegin(GL_POINTS);
			
		for (i = 0; i < 3; i++) 
		{
			glVertex3fv(&ctrlpoints[k][i][0]);
							
		}
		glEnd();
	}	
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
		glOrtho(-50.0, 50.0, -50.0*(GLfloat)h/(GLfloat)w,50.0*(GLfloat)h/(GLfloat)w, -50.0, 50.0);
	else
		glOrtho(-50.0*(GLfloat)w/(GLfloat)h,50.0*(GLfloat)w/(GLfloat)h, -50.0, 50.0, -50.0, 50.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (700, 700);
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

