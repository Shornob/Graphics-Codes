#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>


int p ,q   ,radius1, xc= 0 ,yc= 0 ;

using namespace std;




void plot_point(int x, int y)
{

  glBegin(GL_POINTS);
  glVertex2i(xc+x, yc+y);
  glVertex2i(xc+x, yc-y);
  glVertex2i(xc+y, yc+x);
  glVertex2i(xc+y, yc-x);
  glVertex2i(xc-x, yc-y);
  glVertex2i(xc-y, yc-x);
  glVertex2i(xc-x, yc+y);
  glVertex2i(xc-y, yc+x);
  glEnd();
}






void bresenham_circle(int r)
{
  int x=0,y=r;
  float pk=(5.0/4.0)-r;

  /* Plot the points */
  /* Plot the first point */
  plot_point(x,y);
  int k;
  /* Find all vertices till x=y */
  while(x < y)
  {
    x = x + 1;
    if(pk < 0)
      pk = pk + 2*x+1;
    else
    {
      y = y - 1;
      pk = pk + 2*(x - y) + 1;
    }
    plot_point(x,y);
  }
  glFlush();
}






void display(void)
{
/* clear all pixels */
glClear(GL_COLOR_BUFFER_BIT);

glColor3f(1.0, 0.0, 0.0);//(R,G,B)

//Draw a triangle using line.

//glBegin(GL_LINES);
//glBegin(GL_LINE_STRIP);
glBegin(GL_LINES);


    glVertex3i(600, 0, 0);
    glVertex3i(-600, 0, 0);

     glVertex3i(0, 600, 0);
    glVertex3i(0, -600, 0);





    //glVertex3i(275, 70, 0);

    //glVertex3i(150, 130,0);

glEnd();
/*
glBegin(GL_POLYGON);


    glVertex3i(25, 70, 0);
    glVertex3i(275, 70, 0);
    glVertex3i(150, 200, 0);


glEnd();
*/


glFlush();



  /* Clears buffers to preset values */
  //glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 1.0, 0.0);

  bresenham_circle(radius1);



}
void init(void)
{
/* select clearing (background) color */
glClearColor(0.0, 0.0, 0.0, 0.0);
/* initialize viewing values */
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(-600.0 , 600.0 , -600 , 600.0 );
//glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}
/*
* Declare initial window size, position, and display mode
* (single buffer and RGBA). Open window with “hello”
* in its title bar. Call initialization routines.
* Register callback function to display graphics.
* Enter main loop and process events.
*/
int main(int argc, char** argv)
{

cout<< " Enter X & Y values"<<endl;
cin >> p;
cin >> q;


xc = xc + p ;
yc = yc + q ;
cout << " value of current xc " << xc  << endl;
cout <<  " value of current xc " << yc << endl;

cout<< " Enter Radius" <<endl;
cin >> radius1;

glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(300, 300);
glutInitWindowPosition(300, 100);
glutCreateWindow("hello");
init();
glutDisplayFunc(display);
glutMainLoop();
return 0; /* ISO C requires main to return int. */
}

