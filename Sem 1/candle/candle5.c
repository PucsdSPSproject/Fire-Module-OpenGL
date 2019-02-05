#include "delay.h"
#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>
#include "math_operation.c"

/*static int m=20;*/
static int xpoint=350.0f,ypoint=350.0f;
static float a0=0.0f,a1=0.1f,a2=0.2f,a3=0.25f,a4=0.25f,a5=0.2f,a6=0.15f,a8=-0.15f,a9=-0.2f,a10=-0.25f,a11=-0.25f,a12=-0.2f,a13=-0.1f,b0=2.0f,b1=1.75f,b2=1.5f,b3=1.25f,b4=1.0f,b5=0.75f,b6=0.5f;
static float x[20] = {0.0, 0.0,0.0,0.0, 0.2f,0.3f,0.4f,0.5f,0.6f,0.65f,0.7f,0.75f,0.8f,0.85f,0.9f,1.0,1.0,1.0,1.0};
static int flag1=0,flag2=0,ss=0,ss1=0,sflag=0;

void myIdleFunc(void);
void resize(int w, int h);
void myMouse(int button, int state, int x, int y); 
void start_flame(void);
void move_spline(void);
void drawSpline(void);
float bspline(int i, int k, float t);
void init(void);

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
	if(xpoint>=350 && xpoint<=500 && ypoint<350)
	{
		/*m=20;*/
		if(flag1==0 && ss<10)
		{

			a0-=0.5f;a1-=0.4f;a2-=0.3f;a3-=0.2f; a4-=0.1f;a5-=0.1f;a6-=0.05f;a8-=0.05f;a9-=0.1f;a10-=0.1f;a11-=0.2f;a12-=0.3f;a13-=0.4f;

			ss=ss+1;
			if(ss==10)flag1=1;
		}

		else if(flag1==1)
		{
			a0+=0.5f;a1+=0.4f;a2+=0.3f;a3+=0.2f;a4+=0.1f;a5+=0.1f;a6+=0.05f; a8+=0.05f;a9+=0.1f;a10+=0.1f;a11+=0.2f;a12+=0.3f;a13+=0.4f;

			ss=ss-1;
			if(ss==0)flag1=0;

		}
	}
	else if(xpoint>=200 && xpoint<350 && ypoint<350)
	{
		/*m=20;*/
		if(flag1==0 && ss<10)
		{
			a0+=0.5f;a1+=0.4f;a2+=0.3f;a3+=0.2f;a4+=0.1f;a5+=0.1f;a6+=0.05f; a8+=0.05f;a9+=0.1f;a10+=0.1f;a11+=0.2f;a12+=0.3f;a13+=0.4f;

			ss=ss+1;
			if(ss==10)flag1=1;
		}

		else if(flag1==1)
		{
			a0-=0.5f;a1-=0.4f;a2-=0.3f;a3-=0.2f; a4-=0.1f;a5-=0.1f;a6-=0.05f;a8-=0.05f;a9-=0.1f;a10-=0.1f;a11-=0.2f;a12-=0.3f;a13-=0.4f;

			ss=ss-1;
			if(ss==0)flag1=0;

		}
	}
}

void start_flame()
{
	if(flag1==0 && ss<20)
	{
		a1+=0.1f;a2+=0.2f;a3+=0.25f;a4+=0.25f;a5+=0.2f;a6+=0.15f;a8-=0.15f;a9-=0.2f;a10-=0.25f;a11-=0.25f;a12-=0.2f;a13-=0.1f;b0+=2.0f;b1+=1.75f;b2+=1.5f;b3+=1.25f;b4+=1.0f;b5+=0.75f;b6+=0.5f;

		ss=ss+1;
		if(ss==20)flag1=1;
	}
	else if(flag1==1)
	{
		sflag=1;
		ss=0;
		flag1=0;
		return;
	}	
}

void myMouse(int button, int state,int x1, int y1)
{   
	state=state;
	if (button == GLUT_LEFT_BUTTON)
	{
		xpoint=x1;
		ypoint=y1;
	}
}   

void myIdleFunc(void) 
{
	if(flag2==0 && ss1<m)
	{
		a0-=0.5f;a1-=0.4f;a2-=0.3f;a3-=0.2f; a4-=0.1f;a5-=0.1f;a6-=0.07f;a8-=0.07f;a9-=0.1f;
		b0-=0.1f;

		ss1=ss1+1;
		if(ss1==10)flag2=1;
	}

	else if(flag2==1)
	{
		a0+=0.5f;a1+=0.4f;a2+=0.3f;a3+=0.2f;a4+=0.1f;a5+=0.1f;a6+=0.07f; a8+=0.07f;a9+=0.1f;
		b0+=0.1f;

		ss1=ss1-1;
		if(ss1==0)flag2=0;

	}	
	/*m-=0.4;
	printf("m%d\n",m);
	*/
}

void drawSpline(void)
{
	GLfloat ctrlpoints[1][15][3]={{{a0,b0,0.0},{a1,b1,0.0},{a2,b2,0.0},{a3,b3,0.0},{a4,b4,0.0},{a5,b5,0.0},{a6,b6,0.0},{0.0,0.0,0.0},{a8,b6,0.0},{a9,b5,0.0},{a10,b4,0.0},{a11,b3,0.0},{a12,b2,0.0},{a13,b1,0.0},{a0,b0,0}}};
	static float color=0.0f;
	int j,B,len,k=4;
	static int flag=0;

	int u,v;
	float tmin,tmax,t,x_cord,y_cord;
	len=sizeof(x)/sizeof(x[0]);
	tmin=minimum(x,len);
	tmax=maximum(x,len);
	glClearColor(1.0,1.0,1.0,1.0);

	glClear(GL_COLOR_BUFFER_BIT);

	for(j=0;j<1;j++)
	{	glPointSize(1.0);
		glBegin(GL_LINE_STRIP);

		glColor3f(0.9f,color,0.0f);


		for ( t= tmin; t < tmax; t +=0.005f)
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
		delay(0.05);
		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		glPointSize(2.0);
		glBegin(GL_POINTS);

		for (u =0; u <1; u++)
			for(v=0;v<15;v++)
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
	delay(0.2);
	if (sflag==0)
		start_flame();
	else
		move_spline();

	glPointSize(1.0);
	glBegin(GL_POLYGON);
	glColor3f(0.9f,0.9f,0.9f);
	glVertex3f(-5.0f,0.0f,0.0f);
	glVertex3f(5.0f,0.0f,0.0f);
	glVertex3f(5.0f,-40.0f,0.0f);
	glVertex3f(-5.0f,-40.0f,0.0f);

	glEnd();
	/*glPointSize(5.0);
	  glBegin(GL_LINE_STRIP);
	  glColor3f(0.0f,0.0f,0.0f);
	  glVertex3f(0.0f,0.0f,0.0f);
	  glVertex3f(0.0f,3.0f,0.0f);
	  glEnd();
	  */
	glutSwapBuffers();

	glutPostRedisplay();
	/*delay(rand()%10/100.0);*/
	glFlush();

}


void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
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
	glutCreateWindow("candle");
	init(); 
	glutDisplayFunc(drawSpline); 
	glutReshapeFunc(resize);  

	glutIdleFunc(myIdleFunc);
	glutMouseFunc(myMouse);


	glutMainLoop();
	return 0;  
}
