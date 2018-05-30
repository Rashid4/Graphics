#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>

int width, height;
int rx, ry, cx, cy;

void drawAxis()
{
    glBegin(GL_LINES);
    glVertex2i(-width/2, 0);
    glVertex2i(width/2, 0);
    glVertex2i(0, -height/2);
    glVertex2i(0, height/2);
    glEnd();
}

void drawPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(cx+x, cy+y);
    glVertex2i(cx+x, cy-y);
    glVertex2i(cx-x, cy+y);
    glVertex2i(cx-x, cy-y);
    glEnd();
}

void drawEllipse()
{
    int x = 0, y = ry;
    int d = 4*ry*ry + rx*rx*(1 - 4*ry );
    while(ry*ry*x < rx*rx*y)
    {
        //start from up
        drawPixel(x, y);
        int dE = 4*ry*ry*(2*x + 3);
        int dSE = dE - 8*rx*rx*(y-1);

        if(d > 0)
        {
            d = d + dSE;
            x++;
            y--;
        }
        else
        {
            d = d + dE;
            x++;
        }
    }

    d = ry*ry*(4*x*x + 4*x + 1) + 4*rx*rx*(y*y - 2*y + 1) - 4*rx*rx*ry*ry;
    while(y > 0)
    {
        //start from changed zone
        drawPixel(x, y);
        int dS = 4*rx*rx*(3 - 2*y);
        int dSE = dS + 8*ry*ry*(x+1);
        if(d<0)
        {
            d = d + dSE;
            x++;
            y--;
        }
        else
        {
            d = d + dS;
            y--;
        }
    }
}

void display()
{
    glClearColor(1,1,1,1);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glColor3f(0,0,0);

    drawAxis();
    drawEllipse();

    glFlush();
}

int main(int argc, char *argv[])
{
    printf("Center co-ordinate: ");
    scanf("%d%d", &cx, &cy);
    printf("X radius: ");
    scanf("%d", &rx);
    printf("Y radius: ");
    scanf("%d", &ry);
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
    width = 1300;
    height = 600;
    glutInitWindowSize(width, height);
    glutInitWindowPosition(5, 5);
    glutCreateWindow("Ellipse Drawing");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-width/2, width/2, -height/2, height/2);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
