#include"WETHERELLSHANNON_N_ARY.h"
#include<GLUT/glut.h>
#define minsep 4
int next_pos [1000],x,avg_pos,count;
void xcorCalculator(node *t,int a);
int WIDTH,HEIGHT;
//Initialise Window Dimensions and Background
void Init();

//Main Render Function
void render(void);
node *root;
//Key Call back to enable exit of window in escape key
void keyFunctions(unsigned char key,int x, int y);
int main(int argc, char *argv[])
{   node *temp,*temp1;
    *root =create();
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
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("Tilford Reingold Tree Drawing"); //Window Title
    
    Init();
    
    glutDisplayFunc(render); // Registering function to display tree
    glutKeyboardFunc(keyFunctions);// Registering key callback function
    
    glutMainLoop(); //Main graphics loop which polls for events
}


//calculates the actual x cordinate
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

/*Each integral coordinate is scaled by 100 to be visible appropriately
 in the screen (screen is typically 800x600 or greater), and is off set on the
 left by 50 pixels (as node radius  drawn is 25 pixels)*/

int xCoord(node *NODE,int minX){
    return ( (NODE->xPos - minX) * 50 );
}

/* Open GL (0,0) Refers to botom left corner while algorithm refers to the same
 as the top right corner, hence , node's y value is subtracted from HEIGHT of
 window to set appropriate OpenGL drawing point*/

int yCoord(node *NODE,int WindowHeight){
    return (WindowHeight-((2*(NODE->yPos -1)+1) * 50) );
}




void Init(){
    glClearColor(0.0,0.0,0.0,0.0);//Black as Background Color
    glColor3f(0.0,0.0,0.0);//Black as draw color Color
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,WIDTH,0,HEIGHT);
}



