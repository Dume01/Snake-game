#include <GL/gl.h>
#include <GL/glut.h>
#include "gam.h"
#define COLUMNS 40
#define ROWS 40
#define FPS 10
#include <iostream>

using namespace std;
bool gameOver=false;
//Direction of snake on keyboard callback
extern short sDirection;

//for dispaly
void display_callback();
//for fps and refreshing the page
void timer_callback(int);
void reshape_callback(int,int);
//for keyboard ip
void keyboard_callback(int,int,int);

void init()
{
    glClearColor(0.0,0.0,0.0,1.0);//RGBalpha
    initGrid(COLUMNS,ROWS);
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    // For double buffer one is for displaying the grame and other for drawing
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    //glutInitWindowPosition();
    glutInitWindowSize(500,500);
    glutCreateWindow("Snake Movement");
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    //Register callback which has to be called after a specified number of milli sec
    glutTimerFunc(0,timer_callback,0);
    glutSpecialFunc(keyboard_callback);
    init();
    //For Processing the glut funcion
    glutMainLoop();
    return 0;
}

void display_callback()
{   
    //Clearing color Buffer
    glClear(GL_COLOR_BUFFER_BIT);

    //For drawing the grid
    drawGrid();
    drawSnake();
    drawfood();
    //Swaps Buffers and display new frame
    glutSwapBuffers();
    if(gameOver)
    {
        cout << "The Movement is restricted." << endl;
        exit(0);
    }
}


void reshape_callback(int w,int h)
{   
    //initialize viewport
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    //Change mode to projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //in 3d projection is perspective but in 2d ortho works well
    glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0);// xl,xr,yu,yb,zfar,znear
    glMatrixMode(GL_MODELVIEW);
}

void timer_callback(int)
{   
    //calls display function asap
    glutPostRedisplay();
    glutTimerFunc(1000/FPS,timer_callback,0);
}

void keyboard_callback(int key,int,int)
{
    switch(key)
    {
        case GLUT_KEY_UP:   if(sDirection!=DOWN)
                                sDirection=UP;
        break;
        case GLUT_KEY_DOWN: if(sDirection!=UP)
                                sDirection=DOWN;
        break;   
        case GLUT_KEY_RIGHT: if(sDirection!=LEFT)
                                sDirection=RIGHT;
        break;
        case GLUT_KEY_LEFT: if(sDirection!=RIGHT)
                                sDirection=LEFT;
        break; 
    }
}