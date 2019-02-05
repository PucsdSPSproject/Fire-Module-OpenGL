#include "delay.h"
#include<stdio.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdlib.h>
#include "math_operation.c"
static float a0=0.0f,a1=2.0f,a2=4.0f,a3=5.0f,a4=5.0f,a5=4.0f,a6=3.0f,a8=-3.0f,a9=-4.0f,b0=40.0f,b1=35.0f,b2=30.0f,b3=25.0f,b4=20.0f,b5=15.0f,b6=10.0f;
static float x[20] = { 0.0, 0.0, 0.0,0.0, 0.2,0.3,0.4,0.5,0.6,0.65,0.7,0.75,0.8,0.85,0.9,1.0,1.0,1.0,1.0};
static float s=0.1f,m=0.0f;
static int flag1=0,ss=0;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

float bspline(int i, int k, float t)
{
  
	float coef1, coef2;
	if ( k == 1 )
	{
		if ( i == 0 ) if ( ( x[i] <= t ) && ( t <= x[i+1] ) ) return 1.0;
		if ( ( x[i] < t ) && ( t <= x[i+1] ) ) return 1.0;
		else return 0.0;
	}
	else
	{
		if ( x[i + k - 1] == x[i] ) 
		{
			if ( t == x[i] )
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
void move_spline()
{
	if(flag1==0 && ss<10)
	{
		//a0-=0.5f;a1-=0.4f;a2-=0.3f;a3-=0.2f; a4-=0.1f;a5-=0.1f;a6-=0.07f;a8-=0.07f;a9-=0.1f;
		b0-=1.0f;
		b1-=1.0f;
		b2-=1.0f;
		b3-=1.0f;
		b4-=0.5f;
		b5-=0.5f;
		b6-=0.1f;
		ss=ss+1;
		if(ss==10)flag1=1;
	}
	
	else if(flag1==1)
	{
		//a0+=0.5f;a1+=0.4f;a2+=0.3f;a3+=0.2f;a4+=0.1f;a5+=0.1f;a6+=0.07f; a8+=0.07f;a9+=0.1f;
		b0+=1.0f;
		b1+=1.0f;
		b2+=1.0f;
		b3+=1.0f;
		b4+=0.5f;
		b5+=0.5f;
		b6+=0.1f;
		ss=ss-1;
		if(ss==0)flag1=0;
	
	}	
	
}




void drawSpline(void)
{
  
  GLfloat ctrlpoints[1][15][3]={{{a0,b0,0.0},{a1,b1,0.0},{a2,b2,0.0},{a3,b3,0.0},{a4,b4,0.0},{a5,b5,0.0},{a6,b6,0.0},{0.0,0.0,0.0},{a8,b6,0.0},{a9,b5,0.0},{-5.0,b4,0.0},{-5.0,b3,0.0},{-4.0,b2,0.0},{-2.0,b1,0.0},{a0,b0,0}}};

        static float color=0.0f;
	int j,i=0,B,z,len,k=4;
	static int flag=0;


	float tmin,tmax,t,x_cord,y_cord;
	len=sizeof(x)/sizeof(x[0]);
	tmin=minimum(x,len);
	tmax=maximum(x,len);
	glClearColor(1.0,1.0,1.0,1.0);

	glClear(GL_COLOR_BUFFER_BIT);

	for(j=0;j<1;j++)
	{	glPointSize(1.0);
	  glBegin(GL_LINE_STRIP);
	//	glBegin(GL_POLYGON);
		
		glColor3f(0.9f,color,0.0f);


		for ( t= tmin; t < tmax; t +=0.005)
		{
			x_cord=0.0f;
			y_cord=0.0f;
			for(B=0;B<15;B++)
				{
			 
				x_cord=x_cord+ctrlpoints[j][B][0]*bspline(B,k,t);
				y_cord=y_cord+ctrlpoints[j][B][1]*bspline(B,k,t);
			    
				}	
				    
			
			glVertex3f(x_cord,y_cord,0.0f);
		}
		delay(0.001);
		glEnd();
		
		glColor3f(1.0, 0.0, 0.0);
		glPointSize(2.0);
		glBegin(GL_POINTS);
		
		for (int u =0; u <1; u++)
		  for(int v=0;v<15;v++)
			glVertex3f( ctrlpoints[u][v][0],ctrlpoints[u][v][1] , 0.0 );
		glEnd();
		
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
	//delay(1.0);
	move_spline();
	glPointSize(1.0);
	glBegin(GL_POLYGON);
	glColor3f(0.9f,0.9f,0.9f);
	glVertex3f(-5.0f,2.5f,0.0f);
	glVertex3f(5.0f,2.5f,0.0f);
	glVertex3f(5.0f,-40.0f,0.0f);
	glVertex3f(-5.0f,-40.0f,0.0f);
	
	glEnd();
	
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
