#include<stdio.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdlib.h>
#include "math_operation.c"

GLfloat ctrlpoints1[13][3]={{-9.0,49.0,0.0},{9.0,32.0,0.0},{5.0,25.0,0.0},{3.0,20.0,0.0},{5.0,9.0,0.0},{0.0,3.0,0.0},{-2.2,2.0,0.0},{-6.0,0.8,0.0},{-14.0,4.0,0.0},{-15.0,14.0,0.0},{-9.0,23.0,0.0},{-2.0,30.0,0.0},{-9.0,49.0,0.0}};


GLfloat ctrlpoints2[13][3]={{-13.0,40.0,0.0},{-2.0,27.0,0.0},{-3.0,22.0,0.0},{-5.0,16.0,0.0},{-5.0,9.0,0.0},{-7.0,3.8,0.0},{-8.2,2.0,0.0},{-12.0,0.8,0.0},{-19.0,4.0,0.0},{-20.0,17.0,0.0},{-12.0,23.0,0.0},{-5.0,30.0,0.0},{-13.0,40.0,0.0}};


GLfloat ctrlpoints3[13][3]={{11.0,43.0,0.0},{1.0,30.0,0.0},{8.0,23.0,0.0},{14.0,17.0,0.0},{10.0,4.0,0.0},{6.0,2.0,0.0},{-4.0,2.0,0.0},{3.0,3.8,0.0},{1.0,9.0,0.0},{1.0,16.0,0.0},{-1.0,22.0,0.0},{-2.0,27.0,0.0},{11.0,43.0,0.0}};



static float x[20] = { 0.0, 0.0, 0.0,0.0, 0.4,0.5,0.6,0.65,0.7,0.75,0.8,0.85,0.9,1.0,1.0,1.0,1.0};// -- potato
//static float x[20] = { 0.0,0.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0}; // -- half circle
//static float x[20] = { 0.0,0.0,0.0,0.0,0.0,1.0,2.0,3.0,4.0};

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

float bspline(int i, int k, float t)
{
	float coef1, coef2;
	if ( k == 1 )
	{
		if ( ( x[i] <= t ) && ( t < x[i+1] ) ) return 1.0; 
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






void drawSpline(void)
{
        float t,x_cord,y_cord,tmin,tmax;   
	int j,k=4,i=0,B,z,len;
	len=sizeof(x)/sizeof(x[0]);
	tmin=minimum(x,len);
	tmax=maximum(x,len);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(3.0);
	glBegin(GL_LINE_STRIP);//POLYGON
	glColor3f(1.0, 0.0, 0.0);
	 for ( t= tmin; t < tmax; t +=0.0005)
	{
		x_cord=0.0f;
		y_cord=0.0f;
		for(B=0;B<13;B++)
		{
			x_cord=x_cord+ctrlpoints1[B][0]*bspline(B,k,t);
			y_cord=y_cord+ctrlpoints1[B][1]*bspline(B,k,t);
		}
		glVertex3f(x_cord,y_cord,0.0f);
	}

	glEnd();
	glBegin(GL_LINE_STRIP);//POLYGON
	glColor3f(0.0, 0.0, 1.0);
	 for ( t= tmin; t < tmax; t +=0.0005)
	{
		x_cord=0.0f;
		y_cord=0.0f;
		for(B=0;B<13;B++)
		{
			x_cord=x_cord+ctrlpoints2[B][0]*bspline(B,k,t);
			y_cord=y_cord+ctrlpoints2[B][1]*bspline(B,k,t);
		}
		glVertex3f(x_cord,y_cord,0.0f);
	}

	glEnd();
	glBegin(GL_LINE_STRIP);//POLYGON
	glColor3f(0.0, 1.0, 0.0);
	 for ( t= tmin; t < tmax; t +=0.0005)
	{
		x_cord=0.0f;
		y_cord=0.0f;
		for(B=0;B<13;B++)
		{
			x_cord=x_cord+ctrlpoints3[B][0]*bspline(B,k,t);
			y_cord=y_cord+ctrlpoints3[B][1]*bspline(B,k,t);
		}
		glVertex3f(x_cord,y_cord,0.0f);
	}

	glEnd();
	

	/*glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	for (j =0; j <11; j++)
		glVertex3f( ctrlpoints3[j][0],ctrlpoints3[j][1] , 0.0 );
	glEnd();*/
	glutSwapBuffers();
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
