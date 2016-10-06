
#include "binaryTreeWS.h" //All Tree Making and Walk Related Functions
#include "WetherellShannon.c" // Tree Drawing Algorithm which sets x and y positions with            node structure
#include "drawFunctions.c" // All Functions related to rendering to screen using OpenGL
#include<GLUT/glut.h> // Support for OpenGL windowing and Callbacks

//Initialise Window Dimensions and Background
void Init();

//Main Render Function
void render(void);

//Key Call back to enable exit of window in escape key
void keyFunctions(unsigned char key,int x, int y);

node *root; //Root of Tree to be drawn

//Window dimensions (WIDTH is calculated dynamically based on x values generated)
int WIDTH,HEIGHT;



int main(int argc,char **argv){

    /*Create tree to be drawn and run it through the
     WetherellShannon Algorithm to generate the x and
     y values for each node */
    root=createTree();


    /*Set to MODIFIED to have algorithm make minimum width trees
     that may not be centered over its children (UGLIFICATION)*/
    enum AlgorithmType secondPass=MODIFIED;


    /*Runs Tree Drawing Algorithm in "WetherellShannon.c" using the root of the
    tree generated, the height of the tree and the type of aesthetic required */
    generateWetherellShannon(root,maxHeight,secondPass);

    // Print to terminal node values and the ascribed x and y values
    inorderPrint(root);

    /*WIDTH and HEIGHT given pixel values to draw window that *just fits*
    the given tree*/
    WIDTH=(maxX-minX+1)*100 ;
    HEIGHT=2*(maxHeight+1)*50;

    
    //Initialise Window Size, Setting and Position then create it
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);//
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("Wetherell Shannon Tree Drawing"); //Window Title

    Init();

    glutDisplayFunc(render); // Registering function to display tree
    glutKeyboardFunc(keyFunctions);// Registering key callback function

    while(1)
        glutMainLoop(); //Main graphics loop which polls for events

    return 0;
}

void keyFunctions(unsigned char key,int x,int y){
    if(key==27)//27 corresponds to escape in ASCII
        exit(0); //Exit program is escape key is pressed
}


void render(void){
    glClear(GL_COLOR_BUFFER_BIT);// Set Background
    node *current=root;
    current->status=FIRST_VISIT;
    int x0,y0,x1,y1;
    double slope;
    int xc,yc;
    //In Order Walk and draw edges to left subchild before , right subchild, both edges in white
    while(current != NULL){

        switch(current->status){
            case FIRST_VISIT:
                current->status=LEFT_VISIT;
                if(current->left !=NULL){
                    glColor3f(1.0,1.0,1.0);//White
                    BresenhamLine(xCoord(current->left,minX),yCoord(current->left,HEIGHT),xCoord(current,minX),yCoord(current,HEIGHT));
                    current=current->left;
                    current->status=FIRST_VISIT;
                }
                break;

            case LEFT_VISIT:
                current->status=RIGHT_VISIT;
                if(current->right !=NULL){
                    glColor3f(1.0,1.0,1.0);//White
                    //Draw line
                    BresenhamLine(xCoord(current->right,minX),yCoord(current->right,HEIGHT),xCoord(current,minX),yCoord(current,HEIGHT));
                    current=current->right;
                    current->status=FIRST_VISIT;
                }
                break;

            case RIGHT_VISIT: //Draw node circle in white and fill with red color
                xc=xCoord(current,minX);
                yc=yCoord(current,HEIGHT);
                glColor3f(1.0,0.0,0.0);//Red
                memset(visited,0,2500);//Clear visited from previous fill
                fill(xc,yc,xc,yc,19);
                glColor3f(1.0,1.0,1.0);//White
                MidPointCircle(xc,yc, 20);

                current=current->father;
                break;
        }

    }
}


void Init(){
    glClearColor(0.0,0.0,0.0,0.0);//Black as Background Color
    glColor3f(0.0,0.0,0.0);//Black as draw color Color
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,WIDTH,0,HEIGHT);
}
