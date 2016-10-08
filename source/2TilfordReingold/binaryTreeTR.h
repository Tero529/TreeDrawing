/*! \file binaryTreeTR.h
 * \brief Tree Functions for Tilford Reingold
 
 * Specifies functions to create a binary search tree from user input data or
 * hard coded data (See source code for createTree();) and sets all tree related
 * fields to be used by the Tilford Reingold Tree Drawing Algorithm,
 * Also provides functions for translating integral Wetherell Shannon outputs to
 * window coordinates for drawing.
 */
#ifndef BINARYTREE_TR_H
#define BINARYTREE_TR_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct nodes node; //! node used to refer to a node in the binary tree




//! Node Allocation
/*!A function to allocate space for a fresh node, initilise its
 attributes and return the pointer to it */
/*! \param InputValue value to be stored in node
 \param parent parent of node being created
 */
node *createNode(int InputValue,node *parent);

//!Create Binary Tree to be drawn
/*!Creates a Binary Search Tree using the number of nodes and values of those
 nodes as specified within it */
node *createTree(void);

//! Helper for createTree()
/*! Works from within the createTree() function to find correct position for
 the next node and set related pointers*/
/*! \param inputValues[] List of integers to be used to create BST
    \param n number of nodes
 */
node *treeHelper(int inputValues[],int n);

//! Preorder Walk and Helper Function
/*! Prints the created tree in preorder representation and also assigns maxX , minX ,
 and maxHeight */
/*! \param root root of tree to be traversed */
void preorder(node *root);
 


//! Translates Tilford Reingold Integral x-value into Window coordinate
/*!Each integral coordinate is scaled by 100 to be visible appropriately
 in the screen (screen is typically 800x600 or greater), and is off set on the
 left by 50 pixels (as node radius  drawn is 25 pixels)
 */
/*! \param NODE Node whose x-coordinate is to be extracted
    \param minX minimumX value of entire tree
 */
int xCoord(node *NODE,int minX);

//! Translates Tilford Reingold Integral y-value into Window coordinate
/*! Open GL (0,0) Refers to botom left corner while algorithm refers to the same
 as the top right corner, hence , node's y value is subtracted from HEIGHT of
 window to set appropriate OpenGL drawing point
 */
/*! \param NODE Node whose x-coordinate is to be extracted
 \param WindowHeight The height of created window
 */
int yCoord(node *NODE,int WindowHeight);



//! The maximum y-value amongst all nodes after the tree drawing algorithm is run
int maxHeight=0;

int minX=0;//!< Minimum x -value of all nodes after final positions are set , used to generate window WIDTH
int maxX=0; //!< Maximum x -value of all nodes after final positions are set , used to generate window WIDTH


//! The Tilford Reingold Tree Node
struct nodes{
    int offset; //!< Offset of node from it's parent location
    int thread; //!< Distinguished Pointer for next node on contour

    int value; //!< Data Value to be stored in node
    node *left,  //!< Pointer to Left Son
        *right,  //!< Pointer to Right son
        *father; //!< Pointer to the father
    int xPos, //!< xPos to be set by tree drawing Algorithm
        yPos; //!< xPos to be set by tree drawing Algorithm
    
    //!Enumeration used for Iterative Tree Walks
    enum nodeStatus{FIRST_VISIT,
        LEFT_VISIT ,
        RIGHT_VISIT }
    status;/*!< update during traversal */

};

node *createNode(int InputValue,node *parent){
    node *temp;
    temp=(node*)malloc(sizeof(node));
    temp->value=InputValue;
    temp->left=NULL;
    temp->right=NULL;
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
    
   // printf("How many values? ");
    //scanf("%d",&n);
    n=12;
    int inputValues[]={7,10,4,54,2,6,9,15,1,3,8,25};
    //int inputValues[n];
    int counter=0;
    //for(counter=0;counter<n;counter++)
     //scanf("%d",&inputValues[counter]);
    
    node *root=treeHelper(inputValues,n);

    printf("Tree created is (inorder representation)\n");
    
    
    printf("\n");
    
    return root;
}

//To create Binary Search Tree from given data
node *treeHelper(int inputValues[],int n){
    
    int counter; // Keeps of track of number of node added
    
    node *root;
    root=createNode(inputValues[0],NULL);
    node *current=root;

    for(counter=1;counter<n;counter++){
        current=root;

        while(1){ // Loop until proper position is found

            if(inputValues[counter] <= current->value){
                if(current->left==NULL){
                    current->left=createNode(inputValues[counter],current);
                    break;
                }
                else{
                    current=current->left;
                    continue;
                }
            }
            else {
                if(current->right==NULL){
                    current->right=createNode(inputValues[counter],current);
                    break;
                }
                else{
                    current=current->right;
                    continue;
                }
            }
        }
        
    }
    return root;
}


void preorder(node *root){
    /*!Also run once after tree drawing algorithms set x,y values to decide and
     assign maxX and minX values */
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



int xCoord(node *NODE,int minX){
    return ( (NODE->xPos - minX) * 50 +50);
}

int yCoord(node *NODE,int WindowHeight){
    return (WindowHeight-((2*(NODE->yPos -1)+1) * 50) );
}



#endif

