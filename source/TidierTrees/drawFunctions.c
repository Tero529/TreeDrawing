#ifndef DRAWFUNCTIONS_H
#define DRAWFUNCTIONS_H

#include<stdio.h>
#include<GLUT/glut.h>
#include<math.h>

void BresenhamLine(int x0,int y0,int x1,int y1);
void MidPointCircle(int xc,int yc,int radius);
void CirclePoints(int xc,int yc,int x,int y);
void PutPixel(int x,int y);
int sign(int x);
void fill(int x,int y,int xc,int yc, int radius);
char visited[50][50];

void BresenhamLine(int x0,int y0,int x1,int y1){


    int i;
    int x=x0;
    int y=y0;
    int dx=abs(x1-x0);
    int dy=abs(y1-y0);
    int sign1=sign(x1-x0);
    int sign2=sign(y1-y0);
    int swapFlag=0;
    if(dy>dx){
        int temp=dx;
        dx=dy;
        dy=temp;
        swapFlag=1;
    }
    int decision=2*dy -dx;
    for(i=0;i<dx;i++){
        PutPixel(x,y);
        while(decision>=0){
            decision-= 2*dx;
            if(swapFlag)
                x+=sign1;
            else
                y+=sign2;
        }
        decision+=2*dy;
        if(swapFlag)
            y+=sign2;
        else
            x+=sign1;
    }
    
    
}

void MidPointCircle(int xc,int yc,int radius){

    int x=0;
    int y=radius;
    int d=1-radius;
    int deltaE= 3;
    int deltaSE= -2*radius +5;
    CirclePoints(xc,yc,x,y);
    while(y>x)
    {
        if(d<0)
        {
            d+=deltaE;
            deltaE+=2;
            deltaSE+=2;
        }
        else
        {
            d+=deltaSE;
            deltaE+=2;
            deltaSE+=4;
            y--;
        }
        x++;
        CirclePoints(xc,yc,x,y);
        CirclePoints(xc,yc,x+1,y+1);
    }
    
    
}



void CirclePoints(int xc,int yc,int x,int y){
    PutPixel(xc+x,yc+y);
    PutPixel(xc+y,yc+x);
    PutPixel(xc+y,yc-x);
    PutPixel(xc+x,yc-y);
    PutPixel(xc-x,yc-y);
    PutPixel(xc-y,yc-x);
    PutPixel(xc-y,yc+x);
    PutPixel(xc-x,yc+y);
}

void PutPixel(int x, int y){
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}

void fill(int x,int y,int xc,int yc,int radius){
    int dec=(x-xc)*(x-xc) +(y-yc)*(y-yc);
    
    if(dec < (radius*radius) && visited[radius+(x-xc)][radius+(y-yc)]==0){
        PutPixel(x,y);
        visited[radius+(x-xc)][radius+(y-yc)]=1;
        fill(x,y,xc,yc,radius);
        fill(x,y,xc,yc,radius);
        
        fill(x+1,y+1,xc,yc,radius);
        fill(x+1,y,xc,yc,radius);
        fill(x+1,y-1,xc,yc,radius);
        
        fill(x-1,y+1,xc,yc,radius);
        fill(x-1,y,xc,yc,radius);
        fill(x-1,y-1,xc,yc,radius);
    }
}

int sign(int x){
    if(x>0)
        return 1;
    else if(x<0)
        return -1;
    else
        return 0;
}
#endif

