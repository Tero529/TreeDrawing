
#include "binaryTreeTR.h" //All Tree Making and Walk Related Functions
#include "TilfordReingold.c" // Tree Drawing Algorithm which sets x and y positions with node structure
#include "drawFunctions.c" // All Functions related to rendering to screen using OpenGL
#include<GLUT/glut.h> // Support for OpenGL windowing and Callbacks

void Init();
void render(void);
void keyFunctions(unsigned char key,int x, int y);
node *root;

//Window dimensions (WIDTH IS calculated dynamically based on x values generated)
int WIDTH,HEIGHT;
node *root;


int main(int argc,char **argv){

    /*Create tree to be drawn and run it through the
     TilfordReingold Algorithm to generate the x and
     y values for each node */
    root=createTree();
    generateTilfordReingold(root);
    preorder(root);
    printf("%d %d\n",minX,maxX);


    WIDTH=(maxX-minX+2)*50 ;
    HEIGHT=2*(maxHeight)*50;
    
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("Tilford Reingold Tree Drawing");

    Init();

    glutDisplayFunc(render);
    glutKeyboardFunc(keyFunctions);

    glutMainLoop();

    return 0;
}

void keyFunctions(unsigned char key,int x,int y){
    if(key==27)//27 corresponds to escape in ASCII
        exit(0);
}


void render(void){
    glClear(GL_COLOR_BUFFER_BIT);
    node *current=root;
    current->status=FIRST_VISIT;
    int x0,y0,x1,y1;
    double slope;
    int xc,yc;
    while(current != NULL){

        switch(current->status){
            case FIRST_VISIT:
                current->status=LEFT_VISIT;
                if(current->left !=NULL){
                    glColor3f(1.0,1.0,1.0);
                    BresenhamLine(xCoord(current->left,minX),yCoord(current->left,HEIGHT),xCoord(current,minX),yCoord(current,HEIGHT));
                    current=current->left;
                    current->status=FIRST_VISIT;
                }
                break;

            case LEFT_VISIT:
                current->status=RIGHT_VISIT;
                if(current->right !=NULL){
                    glColor3f(1.0,1.0,1.0);
                    BresenhamLine(xCoord(current->right,minX),yCoord(current->right,HEIGHT),xCoord(current,minX),yCoord(current,HEIGHT));
                    current=current->right;
                    current->status=FIRST_VISIT;
                }
                break;

            case RIGHT_VISIT:
                xc=xCoord(current,minX);
                yc=yCoord(current,HEIGHT);
                glColor3f(1.0,0.0,0.0);
                memset(visited,0,2500);
                fill(xc,yc,xc,yc,24);
                glColor3f(1.0,1.0,1.0);
                MidPointCircle(xc,yc, 25);

                current=current->father;
                break;
        }

    }
}


void Init(){
    glClearColor(0.0,0.0,0.0,0.0);
    glColor3f(0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,WIDTH,0,HEIGHT);
}
