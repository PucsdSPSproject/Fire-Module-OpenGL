#include<stdio.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdlib.h>

  

static float x[6] = {0.0, 10.0, 20.0, 30.0, 40.0,50.0}; 	
static int cnt=0;

void init(void)
{
   glClearColor(1.0, 1.0, 1.0, 0.0);
}

float bspline(int i, int k, float t)
{
	cnt++;
   float term1, term2;
  
   if ( k == 1 )
	{
		if ( ( x[i] <= t ) && ( t < x[i+1] ) ) return 1.0; 
		else return 0.0;
	}
   else
   {
      term1 = (t - x[i])/(x[i + k - 1] - x[i]);
	
      term2 = (x[i + k] - t)/(x[i + k] - x[i+1]);
		
      return ( term1 * bspline(i, k-1, t) + term2 * bspline(i+1,k-1 ,t) );
   }
}


void drawSpline(void)
{
 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   	
  
   	glColor3f(0.0, 0.0, 0.0);
   
  
   	float t,val;   
   	int j,k=4,i=0;
   
	glPointSize(3.0);
	


	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	for ( t= x[i]; t <= x[i + k+1]; t +=0.02)
	{
		
	     glVertex3f( 0.0 + t, 20*bspline(i, k, t), 0.0 );	
		
	}
	glEnd();

      	
      	
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
	for (j = i; j <= i + k; j++)
	   glVertex3f( 0.0 + x[j], 30*bspline(i, k, x[j]) , 0.0 );
	glEnd();
	  



	
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
