#include "delay.h"
#include<stdio.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdlib.h>
#include "math_operation.c"
void init(void);
float bspline(int i, int k, float t);
void move_spline(void);
void drawSpline(void);
void resize(int w, int h);
static float b0=-9.0f,a0=-9.0f,c0=11.0f,a3=-20.0f,b3=-10.0f,c8=10.0f,a9=-5.0f,c4=1.0f,a00=40.0f;
static float x[20] = {0.0f, 0.0f, 0.0f,0.0f, 0.4f,0.5f,0.6f,0.65f,0.7f,0.75f,0.8f,0.85f,0.9f,1.0f,1.0f,1.0f,1.0f};
static int flag1=0,ss=0;

void init(void)
{
	/*glClearColor(1.0, 1.0, 1.0, 0.0);*/
}

float bspline(int i, int k, float t)
{
	float coef1, coef2;
	if ( k == 1 )
	{
		if ( ( x[i] <= t ) && ( t < x[i+1] ) ) return 1.0; //t value jar two knot chya adjacent madhe asel tr
		else return 0.0;
	}
	else
	{
		if ( x[i + k - 1] == x[i] )  //divide by zero error yeil so if use
		{
			if ( t == x[i] ) //t values knot vector madhe astil tr tech conside karayche so mg 1
			//0 asel coef1 tr 0*bspline=0 so only conside thse values use coef value is 1
				coef1 = 1;
			else
				coef1 = 0;
		}
		else
			coef1 = (t - x[i])/(x[i + k - 1] - x[i]);
		if ( x[i + k] == x[i+1] )
		{
			if ( t == x[i + k] )
				coef2 = 1;
			else
				coef2 = 0;
		}
		else
			coef2 = (x[i + k] - t)/(x[i + k] - x[i+1]);
		return ( coef1 * bspline(i, k-1, t) + coef2 * bspline(i+1,k-1 ,t) );
	}
}
void move_spline(void)
{
	if(flag1==0 && ss<10)
	{
		a0-=0.5f; b0+=0.6f; c0+=0.4f;
		a3+=0.1f; b3-=0.2f; c8+=0.3f;
		a9+=0.2f;
		c4-=0.2f;
		a00-=0.5f;
		ss=ss+1;
		if(ss==10)flag1=1;
	}

	else if(flag1==1)
	{
		a0+=0.5f; b0-=0.6f; c0-=0.4f;
		a3-=0.1f; b3+=0.2f; c8-=0.3f;
		a9-=0.2f;
		c4+=0.2f;
		a00+=0.5f;
		ss=ss-1;
		if(ss==0)flag1=0;

	}	

}


void drawSpline(void)
{
	FILE *fp;
	static float color=0.0f;
	int j,B,len,k=4;
	float tmin,tmax,t,x_cord,y_cord;
	static int flag=0;
	GLfloat ctrlpoints[3][13][3]={
		{{a0,a00,0.0},{-2.0f,27.0f,0.0},{-3.0f,22.0f,0.0},{a9,16.0f,0.0},{-5.0f,9.0f,0.0},{-7.0f,3.8f,0.0},{-8.2f,2.0f,0.0},{-12.0f,0.8f,0.0},{-19.0f,4.0f,0.0},{a3,17.0f,0.0},{-12.0f,23.0f,0.0},{-5.0f,30.0f,0.0},{a0,a00,0.0}},

		{{b0,49.0f,0.0},{9.0,32.0f,0.0},{5.0f,25.0f,0.0},{3.0f,20.0f,0.0},{5.0f,9.0f,0.0},{0.0,3.0f,0.0},{-2.2f,2.0f,0.0},{-6.0f,0.8f,0.0},{-12.0f,6.0f,0.0},{b3,14.0f,0.0},{-9.0f,23.0f,0.0},{-2.0f,30.0f,0.0},{b0,49.0f,0.0}},

		{{c0,43.0f,0.0},{1.0f,30.0f,0.0},{8.0f,23.0f,0.0},{14.0f,17.0f,0.0},{c8,4.0f,0.0},{6.0f,2.0f,0.0},{-4.0f,2.0f,0.0},{3.0f,3.8f,0.0},{c4,9.0f,0.0},{1.0f,16.0f,0.0},{-1.0f,22.0f,0.0},{-2.0f,27.0f,0.0},{c0,43.0f,0.0}}};

	fp=fopen("bspline.txt","w+");
	
	len=sizeof(x)/sizeof(x[0]);
	tmin=minimum(x,len);
	tmax=maximum(x,len);
	glClearColor(1.0,1.0,1.0,1.0);

	glClear(GL_COLOR_BUFFER_BIT);

	for(j=0;j<=2;j++)
	{	glPointSize(1.0);
	  glBegin(GL_LINE_STRIP);
	/*glBegin(GL_POLYGON);*/

		glColor3f(0.9f,color,0.0f);


		for ( t= tmin; t < tmax; t +=0.005f)
		{
			x_cord=0.0f;
			y_cord=0.0f;
			for(B=0;B<13;B++)
			{

				x_cord=x_cord+ctrlpoints[j][B][0]*bspline(B,k,t);
				y_cord=y_cord+ctrlpoints[j][B][1]*bspline(B,k,t);

			}	

			fprintf(fp,"%f,%f\n",x_cord,y_cord);
			glVertex3f(x_cord,y_cord,0.0f);
		}
		delay(0.001);
		glEnd();
		/*
		glColor3f(1.0, 0.0, 0.0);
		glPointSize(2.0);
		glBegin(GL_POINTS);

		//for (int u =0; u <3; u++)
		
		for(int v=0;v<13;v++)
			glVertex3f( ctrlpoints[2][v][0],ctrlpoints[2][v][1] , 0.0 );
		glEnd();
		*/
	}



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
	/*delay(1.0);*/
	move_spline();
	glutSwapBuffers();

	glutPostRedisplay();
	delay(rand()%10/100.0);
	glFlush();
	
}








void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char **argv) 
{
	
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 100); 
	glutCreateWindow("bspline");
	init(); 
	glutDisplayFunc(drawSpline); 
	glutReshapeFunc(resize);  
	glutMainLoop();
	return 0;  
}
