#include <GL/glut.h>
#include <GL/gl.h>
#include <ctime>
#include "gam.h"

int gridX,gridY;
//Initial snake lenhth
int snake_len=5;
//Initial direction
short sDirection=RIGHT;
//Initial snake pos
int posX[60]={20,20,20,20,20},posY[60]={20,19,18,17,16};
//Initially food is present
bool food=true;
//For placement of food
int foodX,foodY;
extern bool gameOver;

//Initialize grid
void initGrid(int x,int y)
{
    gridX=x;
    gridY=y;
}

void unit(int,int);
//For Drawing the entire grid
void drawGrid()
{   
    //For making grid through out the window
    for(int x=0;x<gridX;x++)
    {
        for(int y=0;y<gridY;y++)
        {
            unit(x,y);
        }
    }
}
//Helper function for drawGrid function
void unit(int x,int y)
{   
    if(x==0 || y==0 || x==gridX-1 || y==gridY-1)
    {
        glLineWidth(3.0);
        glColor3f(1.0,0.0,0.0);
    }
    else
    {
        glLineWidth(1.0);
        glColor3f(0.0,0.0,0.0);
    }
    //for drawing a line
    glBegin(GL_LINE_LOOP);
        glVertex2f(x,y);
        glVertex2f(x+1,y);
        glVertex2f(x,y+1);
        glVertex2f(x+1,y+1);
    glEnd();
}

//For Drawing food
void drawfood()
{
    if(food)
    {
        random(foodX,foodY);
    }
    food=false;
    glColor3f(1.0,0.0,0.0);
    glRectf(foodX,foodY,foodX+1,foodY+1);
}
//for drawing snake and incrementing its size
void drawSnake()
{   
    for(int i=snake_len-1;i>0;i--)
    {
        posX[i]=posX[i-1];
        posY[i]=posY[i-1];
    }
    if(sDirection==UP)
        posY[0]++;
    else if(sDirection==DOWN)
        posY[0]--;
    else if(sDirection==RIGHT)
        posX[0]++;
    else
        posX[0]--;
    for(int i=0;i<snake_len;i++)
    {
        if(i==0)
            glColor3f(0.0,1.0,0.0);
        else
            glColor3f(0.0,0.0,1.0);
        glRectd(posX[i],posY[i],posX[i]+1,posY[i]+1);
    }
    
    
    if(posX[0]==0 || posX[0]== gridX-1 || posY[0]==0 || posY[0]==gridY-1)
    {
        gameOver=true;
    }
    if(posX[0]==foodX && posY[0]==foodY)
    {
        food=true;
        snake_len++;
        if(snake_len>60)
            snake_len=60;
    }
        
}

//for random positioning of food
void random(int &x,int &y)
{   
    int maxiX=gridX-2;
    int miniX=1;
        int maxiY=gridY-2;
    int miniY=1;
    srand(time(NULL));
    x=miniX+rand()%(maxiX-miniX);
    y=miniY+rand()%(maxiY-miniY);

}