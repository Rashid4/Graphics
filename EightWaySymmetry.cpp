#include <windows.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>

#define width 1200
#define height 600

int n;

void drawPixel(int x, int y)
{
    glVertex2i( x, y );
}

void drawAxis()
{
    //X Axis
    glBegin( GL_LINES );
    drawPixel( -width/2, 0 );
    drawPixel( width/2-1, 0 );
    glEnd();

    //Y Axis
    glBegin( GL_LINES );
    drawPixel( 0, -height/2 );
    drawPixel( 0, height/2-1 );
    glEnd();
}

int findZone(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;

    if(dx>=0 && dy>=0)//first quadrant
    {
        if(dx>dy)return 0;
        return 1;
    }
    else if(dx>=0 && dy<0) //fourth quadrant
    {
        if(dx>abs(dy))return 7;
        return 6;
    }
    else if(dx<0 && dy>=0) //second quadrant
    {
        if(abs(dx)>dy)return 3;
        return 2;
    }
    else //third quadrant
    {
        if(dx<dy)return 4;
        return 5;
    }
}

void drawLine(int x0, int y0, int x1, int y1, int zone)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int d = 2*dy - dx;
    int dE = 2*dy;
    int dNE = 2*(dy - dx);

    do
    {
        if( zone == 0)
        {
            glColor3f( 1, 0, 0 );
            drawPixel( x0, y0 );
        }
        else if( zone == 1 )
        {
            glColor3f( 1, 0, 0 );
            drawPixel( y0, x0 );
        }
        else if( zone == 2 )
        {
            glColor3f( 0, 1, 0 );
            drawPixel( -y0, x0 );
        }
        else if( zone == 3 )
        {
            glColor3f( 0, 1, 0 );
            drawPixel( -x0, y0 );
        }
        else if( zone == 4 )
        {
            glColor3f( 0, 0, 1 );
            drawPixel( -x0, -y0 );
        }
        else if( zone == 5 )
        {
            glColor3f( 0, 0, 1 );
            drawPixel( -y0, -x0 );
        }
        else if( zone == 6 )
        {
            glColor3f( 0, 1, 1 );
            drawPixel( y0, -x0 );
        }
        else if( zone == 7 )
        {
            glColor3f( 0, 1, 1 );
            drawPixel( x0, -y0 );
        }
        if( d<0 )
        {
            x0++;
            d += dE;
        }
        else
        {
            x0++;
            y0++;
            d += dNE;
        }
    }
    while( x0<x1 );
}

void display()
{
    glClearColor( 1, 1, 1, 1 );
    glClear( GL_COLOR_BUFFER_BIT );
    glColor3f( 0, 0, 0 );

    drawAxis();

    int i;

    for( i=0; i<n; i++ )
    {
        glBegin( GL_POINTS );

        int x0 = rand()%width - width/2;
        int y0 = rand()%height - height/2;
        int x1 = rand()%width - width/2;
        int y1 = rand()%height - height/2;

        int zone = findZone( x0, y0, x1, y1 );
        if( zone == 0 )drawLine( x0, y0, x1, y1, zone );
        else if( zone == 1 )drawLine( y0, x0, y1, x1, zone );
        else if( zone == 2 )drawLine( y0, -x0, y1, -x1, zone );
        else if( zone == 3 )drawLine( -x0, y0, -x1, y1, zone );
        else if( zone == 4 )drawLine( -x0, -y0, -x1, -y1, zone );
        else if( zone == 5 )drawLine( -y0, -x0, -y1, -x1, zone );
        else if( zone == 6 )drawLine( -y0, x0, -y1, x1, zone );
        else if( zone == 7 )drawLine( x0, -y0, x1, -y1, zone );

        glEnd();
    }

    glFlush();
}

int main(int argc, char **argv)
{
    printf("Enter number of lines: ");
    scanf("%d", &n);

    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE );
    glutInitWindowSize( width, height );
    glutInitWindowPosition( 0, 0 );
    glutCreateWindow( "8-Way Symmetry" );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( -width/2, width/2-1, -height/2, height/2 );

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
