#include <windows.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>

int x0,y0, x1,y1, n, w, h;

int findZone()
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

void drawLine()
{
    int zone = findZone();
    printf("Zone = %d\n",zone);
    int dx = x1-x0;
    int dy = y1-y0;
    if(zone == 0)
    {
        glColor3f(1,0,0);
        int d = 2*dy-dx;
        int dE = 2*dy;
        int dNE = 2*(dy-dx);
        int x = x0, y = y0;
        do
        {
            glVertex2i(x,y);
            if(d<0)
            {
                x++;
                d+=dE;
            }
            else
            {
                x++;
                y++;
                d+=dNE;
            }
        }
        while(x<x1);
    }
    else if(zone == 1)
    {
        glColor3f(1,0,0);
        int d = dy-2*dx;
        int dN = -2*dx;
        int dNE = 2*(dy-dx);
        int x = x0, y = y0;
        do
        {
            glVertex2i(x,y);
            if(d<0)
            {
                x++;
                y++;
                d+=dNE;
            }
            else
            {
                y++;
                d+=dN;
            }
        }
        while(y<y1);
    }
    else if(zone == 2)
    {
        glColor3f(0,1,0);
        int d = -dy-2*dx;
        int dN = -dx*2;
        int dNW = -2*(dy+dx);
        int x = x0, y = y0;
        do
        {
            glVertex2i(x,y);
            if(d<0)
            {
                y++;
                d += dN;
            }
            else
            {
                x--;
                y++;
                d+=dNW;
            }
        }
        while(y<y1);
    }
    else if(zone == 3)
    {
        glColor3f(0,1,0);
        int d = -2*dy-dx;
        int dW = -2*dy;
        int dWN = -2*(dx+dy);
        int x=x0, y=y0;
        do
        {
            glVertex2i(x,y);
            if(d<0)
            {
                x--;
                y++;
                d+=dWN;
            }
            else
            {
                x--;
                d+=dW;
            }
        }
        while(x>x1);
    }
    else if(zone == 4)
    {
        glColor3f(0,0,1);
        int d = dx - 2*dy;
        int dW = -2*dy;
        int dWS = 2*(dx-dy);
        int x=x0, y=y0;
        do
        {
            glVertex2i(x,y);
            if(d<0)
            {
                x--;
                d+=dW;
            }
            else
            {
                x--;
                y--;
                d+=dWS;
            }
        }
        while(x>x1);
    }
    else if(zone == 5)
    {
        glColor3f(0,0,1);
        int d = 2*dx-dy;
        int dS = 2*dx;
        int dSW = 2*(dx-dy);
        int x=x0, y=y0;
        do
        {
            glVertex2i(x,y);
            if(d<0)
            {
                x--;
                y--;
                d+=dSW;
            }
            else
            {
                y--;
                d+=dS;
            }
        }
        while(y>y1);
    }
    else if(zone == 6)
    {
        glColor3f(1,0,1);
        int d = 2*dx+dy;
        int dS = 2*dx;
        int dSW = 2*(dx+dy);
        int x=x0, y=y0;
        do
        {
            glVertex2i(x,y);
            if(d<0)
            {
                y--;
                d+=dS;
            }
            else
            {
                x++;
                y--;
                d+=dSW;
            }
        }
        while(y>y1);
    }
    else if(zone == 7)
    {
        glColor3f(1,0,1);
        int d = 2*dy+dx;
        int dE = 2*dy;
        int dES = 2*(dx+dy);
        int x=x0, y=y0;
        do
        {
            glVertex2i(x,y);
            if(d<0)
            {
                x++;
                y--;
                d+=dES;
            }
            else
            {
                x++;
                d+=dE;
            }
        }
        while(x<x1);
    }
}

void drawAxis()
{
    //X Axis
    glBegin(GL_LINES);
    glVertex2i(-w/2,0);
    glVertex2i(w/2,0);
    glEnd();

    //Y Axis
    glBegin(GL_LINES);
    glVertex2i(0,-h/2);
    glVertex2i(0,h/2);
    glEnd();
}

void display()
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w/2, w/2-1, -h/2, h/2-1);

    drawAxis();

    int i;
    for(i=0; i<n; i++)
    {
        glBegin(GL_POINTS);
        x0 = rand()%w - w/2;
        x1 = rand()%w - w/2;
        y0 = rand()%h - h/2;
        y1 = rand()%h - h/2;
        drawLine();
        glEnd();
    }

    glFlush();
}

int main(int argc, char *argv[])
{
    w = 1200;
    h = 640;
    printf("Enter number of line: ");
    scanf("%d",&n);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(w, h);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Mid-Point line drawing algorithm");

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
