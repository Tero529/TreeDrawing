/*! \file mainTR.c
 * \brief Main Driver for Tilford Reingold Drawing
 
 * This file begins execution by creating a Binary Search Tree, and feeding it through
 * the Tilford Reingold Tree Placement Algorith before using the generated x and y values
 * to draw a tree to screen using the OpenGL API for drawing and GLUT for windowing
 */

#include "binaryTreeTR.h" //All Tree Making and Walk Related Functions
#include "TilfordReingold.h" // Tree Drawing Algorithm which sets x and y positions with node structure
#include "drawFunctionsTR.h" // All Functions related to rendering to screen using OpenGL
#include<GLUT/glut.h> // Support for OpenGL windowing and Callbacks
//!Initialise Draw Settings
void Init();

//! Function to render objects to screen
void render(void);

//! Key Callback Functions
/*! Function sets a key callback for the escape key,
 *  so that the application quits whenever the user
 *  pressed the escape key
 */
/*! \param key The key pressed on the keyboard
 * \param x X-coordinate of mouse when key is pressed
 * \param y Y-coordinate of mouse when key is pressed
 */
void keyFunctions(unsigned char key,int x, int y);

node *root; //!< Root of Tree to be drawn


int WIDTH, //!< Window WIDTH, value genearted dynamically depending on node coordinates gotten
HEIGHT;//!< Window HEIGHT, value genearted dynamically depending on node coordinates gotten


//! Startpoint of Application
int main(int argc,char **argv){
    
    /*! First runs createTree() to create tree to be drawn
     */
    root=createTree();
    
    /*! It then runs Tree Drawing Algorithm in "TilfordReingold.h" using the root of the
     tree generated earlier*/
    generateTilfordReingold(root);
    
    /*! A Preorder walk is then performed to obtain minX,maxX and 
     * maxHeight and see results of TR */
    preorder(root);

    /*! WIDTH and HEIGHT are given given pixel values so as to
     * yield a window that *just fits* the given tree
     */
    WIDTH=(maxX-minX+2)*50 ;
    HEIGHT=2*(maxHeight)*50;
    
    
    /*! Uses GLUT to initiliaze window with the created WIDTH
     *and HEIGHT and places window at top left of screen
     */
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);//
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("Wetherell Shannon Tree Drawing"); //Window Title
    
    /*! Then Initialise Drawing settings wiith Init() */
    Init();

    
    glutDisplayFunc(render); // Registering function to display tree
    glutKeyboardFunc(keyFunctions);// Registering key callback function
    
    glutMainLoop(); //Main graphics loop which polls for events
    
    return 0;

}


void keyFunctions(unsigned char key,int x,int y){
    /*! polls for event when pressed key==27 */
    if(key==27)//27 corresponds to escape in ASCII
        exit(0); //Exit program is escape key is pressed
}


void render(void){
    glClear(GL_COLOR_BUFFER_BIT);// Set Background
    node *current=root;
    current->status=FIRST_VISIT;
    int xc,yc;
    /*! Performs an Inorder walk and drawing First all the edges (left edges then right edges) in white
     * Then fill area within each node circle using fill() in red
     * and finally draws a boundary around it in white
     */
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
    /*! Both Background and Drawing colour are set to Black
     *  The drawing mode is set to projection in orthographic mode
     *  with size equal to that of the window
     */
    glClearColor(0.0,0.0,0.0,0.0);//Black as Background Color
    glColor3f(0.0,0.0,0.0);//Black as draw color Color
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,WIDTH,0,HEIGHT);
}
