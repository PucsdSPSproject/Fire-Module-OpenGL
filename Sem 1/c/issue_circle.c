#include<math.h>
#include<stdio.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
float color=0.0f;
int flag=0;
void myDisplay()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glScalef(color,color,color);
	int number=40,i;
	float radius=0.4f;
	float twoPi=2.0*3.1452423;
	glBegin(GL_POLYGON);
	glColor3f(0.9f,color,0.0f);	
	glVertex2f(0.0f,0.0f);
	for(i=0;i<=40;i++)
		glVertex2f(radius*cosf(i*twoPi/number),radius*sinf(i*twoPi/number));
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
	glutCreateWindow("My project " );
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}
