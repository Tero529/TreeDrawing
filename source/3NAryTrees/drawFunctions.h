
#ifndef DRAWFUNCTIONSWS_H
/*! \breif Header Guard to Prevent Redeclaration
 */
#define DRAWFUNCTIONSWS_H
#include<stdio.h>
#include<GLUT/glut.h>
#include<math.h>

/*! \file drawFunctions.h
    \brief Algorithms for Line, Circle Drawinng and Circle Fill
 
 * This file contains functions to translate coordinates and
 * to drawn primitives on the screen using
 * 1. OpenGL API for pixel drawing
 * 2. Generalised Bresenham's Midpoint Algorithm for Line Drawing
 * 3. Midpoint Circle Algorithm
 * 4. 4 Neighbour Flood Fill, for filling circles
 */


//! Bresenham's Midpoint Line Drawing
/*! Uses a generalised version of Bresenham's midpoint algorithm
 * to draw a line from (x0,y0) to (x1,y1)
 */
/*! \param x0 x-coordinate of point drawn from
    \param y0 y-coordinate of point drawn from
    \param x1 x-coordinate of point drawn to
    \param y1 y-coordinate of point drawn to*/
void BresenhamLine(int x0,int y0,int x1,int y1);



//! Midpoint Circle Drawing
/*! Uses the midpoints algorithm and 8-way symmetry
 * to draw a circle with given centre and radius.
 * It a second circle with the same centre but an
 * incremented radius to ensure thick boundarys
 */
/*! \param xc x-coordinate of circle's centre
    \param yc y-coordinate of circle's centre
    \param radius Radius of the circle to be drawn
 */
void MidPointCircle(int xc,int yc,int radius);


//! Draws 8 Points on Circle
/*! Utilises 8-way symmetery of a circle to translate
 * one point generated from Midpoint Circle into 8.
 * Midpoint Circle generates points such that center is at origin
 * thus points must be added to center in the drawing algorithm
 */
/*! \param xc,yc coordinates of circle center
 *  \param x,y coordinates of circle if centered at origin
 */
void CirclePoints(int xc,int yc,int x,int y);

//! Puts a Pixel at (x,y) on the screen
void PutPixel(int x,int y);

//! Sign Determiner
/*! \param x Input Number
    \return 1 is x is positive
    \return -1 if x is negative
    \return 0 if x is zero
*/
int sign(int x);


//! 4-Neighbour Fill
/*! Uses a 4 -neighbour approach to filling
*  all points within circle of given centre and radius
*/
/*! \param xc,yc coordinates of circle center
    \param radius Radius of circle to fill
*/
void fill(int x,int y,int xc,int yc, int radius);

//! Visit Matrix Used for Filling Algorithm
/*! visit matrix which is memset to 0 before calling the fill algorithm.
 */
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
    
    //! To Support cases where | Slope | > 1, values of dy and dx are swapped it dy > dx and swapFlag is set to 1
    if(dy>dx){
        int temp=dx;
        dx=dy;
        dy=temp;
        swapFlag=1;
    }
    
    /*!  <b> decision </b>  is the decision variable who's sign decides which pixel to draw */
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
    
    int d=1-radius;//! <b> d </b> is the decision variable (East pixel is chosen if negative, South East Otherwise
    
    //! <b> deltaE and deltaSE </b> Second Order Differences
    int deltaE= 3;
    int deltaSE= -2*radius +5;
    
    CirclePoints(xc,yc,x,y);
    
    while(y>x)
    {
        if(d<0)//Choose East Pixel
        {
            d+=deltaE;
            deltaE+=2;
            deltaSE+=2;
        }
        else//Choose South-East Pixel
        {
            d+=deltaSE;
            deltaE+=2;
            deltaSE+=4;
            y--;
        }
        x++;
        //Draw Two circles to obtain a thick boundary
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
    
    /*! Fill function draws the given pixel and calls its 4 neighbours (down,up,right,left) if it
     * is inside the given circle and updates the visited matrix for its current point
     */
    if(dec < (radius*radius) && visited[radius+(x-xc)][radius+(y-yc)]==0){
        PutPixel(x,y);
        
        visited[radius+(x-xc)][radius+(y-yc)]=1;
        
        fill(x,y-1,xc,yc,radius);
        fill(x,y+1,xc,yc,radius);
        fill(x+1,y,xc,yc,radius);
        fill(x-1,y,xc,yc,radius);
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

