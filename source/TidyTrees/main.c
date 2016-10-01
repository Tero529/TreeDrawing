#ifndef DRAWFUNCTIONS_H
#define DRAWFUNCTIONS_H
#include "binaryTree.h"
#include "WetherellShannon.c"
#include "drawFunctions.c"
#include<GLUT/glut.h>

#define POSTIVE 1
#define NEGATIVE 0

void Init();
void render(void);
node *root;
//Window dimensions
int WIDTH=1000,HEIGHT=1000;
#define LEFT_OFFSET 250

int main(int argc,char **argv){

    /*Create tree to be drawn and run it through the
     WetherellShannon Algorithm to generate the x and
     y values for each node */

    root=createTree();
    enum AlgorithmType secondPass=MODIFIED;
    generateWetherellShannon(root,maxHeight,secondPass);
    inorderPrint(root);
    WIDTH=(maxX-minX) * 100 +400;
    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("Wetherell Shannon Tree Drawing");

    Init();

    glutDisplayFunc(render);
    glutMainLoop();

    return 0;
}

void render(void){
    glClear(GL_COLOR_BUFFER_BIT);
    node *current=root;
    current->status=FIRST_VISIT;
    int x0,y0,x1,y1;
    double slope;
    while(current != NULL){
        
        switch(current->status){
            case FIRST_VISIT:
                current->status=LEFT_VISIT;
                if(current->left !=NULL){
                    BresenhamLine(xCoord(current->left),yCoord(current->left,HEIGHT),xCoord(current),yCoord(current,HEIGHT));
                    current=current->left;
                    current->status=FIRST_VISIT;
                }
                break;
                
            case LEFT_VISIT:
                current->status=RIGHT_VISIT;
                if(current->right !=NULL){
                    BresenhamLine(xCoord(current->right),yCoord(current->right,HEIGHT),xCoord(current),yCoord(current,HEIGHT));
                    current=current->right;
                    current->status=FIRST_VISIT;
                }
                break;
                
            case RIGHT_VISIT:
                MidPointCircle(xCoord(current),yCoord(current,HEIGHT), 25);
                current=current->father;
                break;
        }
        
    }
    
}

void Init(){
    glClearColor(0.2,0.2,0.2,0);
    glColor3f(0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,WIDTH,0,HEIGHT);
}

#endif
