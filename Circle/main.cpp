#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define WIDTH 1000
#define HEIGHT 600

int cx, cy, r;

void drawAxis()
{
    glBegin( GL_LINES );
    glVertex2i( -WIDTH/2, 0 );
    glVertex2i( WIDTH/2, 0 );
    glEnd();

    glBegin( GL_LINES );
    glVertex2i( 0, -HEIGHT/2 );
    glVertex2i( 0, HEIGHT/2 );
    glEnd();
}

void drawPixel(int x, int y, int cenx, int ceny)
{
    glVertex2i( cenx+x, ceny+y );
    glVertex2i( cenx+y, ceny+x );
    glVertex2i( cenx-x, ceny+y );
    glVertex2i( cenx-y, ceny+x );
    glVertex2i( cenx-x, ceny-y );
    glVertex2i( cenx-y, ceny-x );
    glVertex2i( cenx+x, ceny-y );
    glVertex2i( cenx+y, ceny-x );
}

void drawCircle()
{
    int limit = r/sqrt(2);
    int d = 5 - 4*r;
    int x = 0, y = r;
    int dE = 8*x + 12;
    int dSE = 8*(x-y) + 20;
    do
    {
        drawPixel( x, y, cx, cy );
        if( d<0 )
        {
            x++;
            dE = 8*x + 12;
            d += dE;
        }
        else
        {
            x++;
            y--;
            dSE = 8*(x-y) + 20;
            d += dSE;
        }
    }
    while( x<limit+1 );
}

void display()
{
    glClearColor( 1, 1, 1, 1 );
    glClear( GL_COLOR_BUFFER_BIT );
    glColor3f( 0, 0, 0 );

    drawAxis();

    glBegin( GL_POINTS );
    drawCircle();
    glEnd();

    glFlush();
}

int main(int argc, char *argv[])
{
    printf("Enter center: ");
    scanf("%d%d",&cx, &cy);
    printf("Enter radius: ");
    scanf("%d",&r);

    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize( WIDTH, HEIGHT );
    glutInitWindowPosition( 0, 0 );
    glutCreateWindow( "Circle Drawing" );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( -WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2 );

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
