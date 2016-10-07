/*! \file main.c
 * \brief Extension to Accomodate N-ary Trees
 
 *  Through this code we have extended the algorithm by taking inspiration
 * from the papers by Wetherell Shannon and tilford Reinfold for positioning nodes of a binary
 *  tree to accomodate an arbitrary number of children. As such it draws
 *  an n-ary tree using many of the same concepts as the aforementioned algorithms.
 \see WetherellShannon.h TilfordReingold.h binaryTreeTF.h binaryTreeWS.h
 */

#include "nAry.h" //All Tree Making Functions
#include "drawFunctions.h" //All Rendering to Screen and OpenGL related functions
#include<GLUT/glut.h> //Windowing and Callback Library

#define minsep 2 //!<Minimum Seperation of nodes on the same level


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

//! Recursive Preorder Drawing Walk
/*! Uses coordinates generated to Draw the given tree
 * \n Walks along the tree in preorder and drawing each
 *  edge from node being traversed to its parent, before 
 *  going to it's sibling.
 *  Once all sibling's edges are drawn, nodes are drawn
 *  in the reverse order, before moving on the parent.
 *  Does not draw the root node, which is drawn from render(void);
 */
/*!
 \param t The current node being traversed (preorder)
 */
void draw(node *t);



int next_pos [1000],
x,
avg_pos,
count;

//!Shift by Modifiers
/*! Shifts the X-Coordinates from the initial 
 *  walk by the modifier values to arrive at
 *  actual/final x-coordinate values
 */
void xcorCalculator(node *t,int a);

node *root; //!< Root of Tree to be drawn

int WIDTH, //!< Window WIDTH, value genearted dynamically depending on node coordinates gotten
HEIGHT;//!< Window HEIGHT, value genearted dynamically depending on node coordinates gotten



int main(int argc, char *argv[])
{
    node *temp,
    *temp1;
    root= create(); //Prompt user and create the tree
    temp=root;
    
    for(x=0;x<1000;x++){//intialization for the starting  x cordinate to be 1
        next_pos[x]=1;
    }
    
    //preorder traversal to assign the x cordinates
    while(temp!=NULL){
       if(temp->ce==NULL||temp->ce->tr==1){
            if(temp->ce==NULL){// when the node has no child
                temp->xcor=next_pos[temp->ycor];
                temp->mod=0;
                temp->tr=1;
                next_pos[temp->ycor]+=minsep;
            }else{//when all its children are traversed
                avg_pos=0;
                count=0;
                temp1=temp->c;
                while(temp1!=NULL){
                    avg_pos=avg_pos+temp1->xcor;
                    count++;
                    temp1=temp1->s;
                }
                avg_pos=avg_pos/count;
                if(next_pos[temp->ycor]>avg_pos){//when the next available position is the x cordinate
                    temp->mod=next_pos[temp->ycor]-avg_pos;
                    next_pos[temp->ycor]+=minsep;
                    temp->xcor=next_pos[temp->ycor];
                    temp->tr=1;
                }else{//when the average of the child position is the x cordinate
                    next_pos[temp->ycor]=avg_pos+minsep;
                    temp->xcor=avg_pos;
                    temp->mod=0;
                    temp->tr=1;
                }
            }
            if(temp->s!=NULL){//going to the sibling if any more left
                temp=temp->s;
            }else{//traversing to the parent
                temp=temp->p;
            }
       }else{
            temp=temp->c;//going to the child
       }
    }
    xcorCalculator(root,0);
    preorder(root);
    
    
    WIDTH=(maxX-minX+2)*50 ;
    HEIGHT=2*(maxY)*50;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("N-ary Tree Drawing"); //Window Title
    
    Init();
    
    glutDisplayFunc(render); // Registering function to display tree
    glutKeyboardFunc(keyFunctions);// Registering key callback function
    
    glutMainLoop(); //Main graphics loop which polls for events
}


void xcorCalculator(node *t,int a){
    if(t!=NULL){
        t->xcor+=a;
        t->mod+=a;
        t=t->c;
        while(t!=NULL){
            xcorCalculator(t,t->p->mod);
            t=t->s;
        }
    }

}

void keyFunctions(unsigned char key,int x,int y){
    /*! polls for event when pressed key==27 */
    if(key==27)//27 corresponds to escape in ASCII
        exit(0); //Exit program is escape key is pressed
}


void render(void){
    glClear(GL_COLOR_BUFFER_BIT);// Set Background
    
    node *current=root;
    
    draw(current); // Draws All Except Root Node
    
    int xc=xCoord(root,0);
    int yc=yCoord(root,HEIGHT);
    
    glColor3f(1.0,1.0,1.0); //White
    MidPointCircle(xc,yc,20);
    glColor3f(1.0,0.0,0.0); //Red
    memset(visited,0,2500); //Clear Visited Buffer
    fill(xc,yc,xc,yc,19);
    }


void draw(node *t){
    node *temp;
    if(t!=NULL){
        t=t->c;// Skip Root node as it has no parent
        
        while(t!=NULL){
            
            glColor3f(1.0,1.0,1.0);//White
            BresenhamLine(xCoord(t->p,0),yCoord(t->p,HEIGHT),xCoord(t,0),yCoord(t,HEIGHT));
            
            draw(t);
            
            int xc=xCoord(t,0);
            int yc=yCoord(t,HEIGHT);
            
            glColor3f(1.0,1.0,1.0); //White
            MidPointCircle(xc,yc,20);
            
            glColor3f(1.0,0.0,0.0);//Red
            memset(visited,0,2500);// Clear visitation buffer
            
            fill(xc,yc,xc,yc,19);
            
            t=t->s;// Move on to sibling
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

