#ifndef BINARYTREE_TR_H
#define BINARYTREE_TR_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct nodes node;
node *createNode(int InputValue,node *current);
node *createTree(void);
node *treeHelper(int inputValues[],int n);
void preorder(node *root);
int xCoord(node *NODE,int minX);
int yCoord(node *NODE,int WindowHeight);


/* The maximum y-value amongs all nodes after the tree drawing algorithm is
 run */
int maxHeight=0;
/* The minimum and maximum x-values of the nodes after the tree drawing
 algorihtm, It is used to calculate the width of the subsequently created window */
int minX=0;
int maxX=0;

struct nodes{
    int xPos,yPos;
    int offset;
    int thread;
    int value;
    enum nodeStatus{FIRST_VISIT , LEFT_VISIT , RIGHT_VISIT } status; //Status field used to iterative tree walks
    node *left,*right,*father;
};

node *createNode(int InputValue,node *parent){
    node *temp;
    temp=(node*)malloc(sizeof(node));
    temp->value=InputValue;
    temp->left=NULL;
    temp->left=NULL;
    temp->xPos=0;
    temp->offset=0;
    temp->yPos=0;
    temp->thread=0;
    temp->father=parent;
    return temp;
}



node *createTree(void){
    int n;
    /*Commented Lines can be uncommented to enable/disable user defined tree drawing */
    
    //printf("How many values? ");
    //scanf("%d",&n);
    n=12;
    int inputValues[]={7,10,4,54,2,6,9,15,1,3,8,25};
    int counter=0;
    /*for(counter=0;counter<n;counter++)
     scanf("%d",&inputValues[counter]);
     */
    node *root=treeHelper(inputValues,n);
    printf("Tree created is (inorder representation)\n");
    preorder(root);
    
    
    printf("\n");
    
    return root;
}

//To create Binary Search Tree from given data
node *treeHelper(int inputValues[],int n){
    
    int counter; // Keeps of track of number of node added
    
    node *root=createNode(inputValues[0],NULL);
    node *current=root;
    
    for(counter=1;counter<n;counter++){
        current=root;
        while(1){
            if(inputValues[counter] <= current->value){
                if(current->left==NULL){
                    current->left=createNode(inputValues[counter],current);
                    break;
                }
                else
                    current=current->left;
            }
            else {
                if(current->right==NULL){
                    current->right=createNode(inputValues[counter],current);
                    break;
                }
                else
                    current=current->right;
            }
        }
    }
    return root;
}


void preorder(node *root){
    if(root!=NULL){
        if(root->xPos < minX)
            minX=root->xPos;
        if(root->xPos > maxX)
            maxX=root->xPos;
        if(root->yPos >maxHeight)
            maxHeight=root->yPos;
        printf("(%d, %d) for value: %d\n",root->xPos,root->yPos,root->value);
        preorder(root->left);
        preorder(root->right);
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



#endif

