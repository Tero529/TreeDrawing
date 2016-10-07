/*! \file binaryTreeWS.h
 * \brief Tree Functions for Wetherell Shannon
 
 * Specifies functions to create a binary search tree from user input data or
 * hard coded data (See source code for createTree();) and sets all tree related
 * fields to be used by the Wetherell Shannon Tree Drawing Algorithm,
 * Also provides functions for translating integral Wetherell Shannon outputs to
 * window coordinates for drawing.
 */
#ifndef BINARYTREE_H
#define BINARYTREE_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct nodet node;

//! The maximum y-value amongst all nodes after the tree drawing algorithm is run
int maxHeight=0;

int minX=200;//!< Minimum x -value of all nodes after finar positions are set , used to generate window WIDTH
int maxX=0; //!< Maximum x -value of all nodes after finar positions are set , used to generate window WIDTH


//! Node Allocation
/*!A function to allocate space for a fresh node, initilise its
attributes and return the pointer to it */
/* \param InputValue value to be stored in node
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
/* \param inputValues[] List of integers to be used to create BST
   \param n number of nodes
 */
node *treeHelper(int inputValues[],int n);

//! Inorder Walk and Helper Function
/*! Prints the created tree in inorder representation and also assigns maxX , minX ,
and maxHeight */
/*! \param root root of tree to be traversed */
void inorderPrint(node *root);

//! Sets height field of each node
/*! Set nodeheight field of all nodes in tree with given root 
 * through a pre order walk*/
/*! \param root root of tree to be traversed 
    \param height height of root (used to set nodeHeight field for subsequent nodes)
 */
void setHeight(node *root,int height);


//! Translates Wetherell Shannon Integral x-value into Window coordinate
/*!Each integral coordinate is scaled by 100 to be visible appropriately
 in the screen (screen is typically 800x600 or greater), and is off set on the
 left by 50 pixels (as node radius  drawn is 25 pixels)
 */
/*! \param NODE Node whose x-coordinate is to be extracted
   \param minX minimumX value of entire tree
 */
int xCoord(node *NODE,int minX);

//! Translates Wetherell Shannon Integral y-value into Window coordinate
/*! Open GL (0,0) Refers to botom left corner while algorithm refers to the same
 as the top right corner, hence , node's y value is subtracted from HEIGHT of
 window to set appropriate OpenGL drawing point
*/
/*! \param NODE Node whose x-coordinate is to be extracted
   \param WindowHeight The height of created window
 */
int yCoord(node *NODE,int WindowHeight);

//! The Wetherell Shannon Tree Node
struct nodet{
	int value;
	node *left, //!< Pointer to Left Son
        *right, //!< Pointer to Right son
        *father;//!< Pointer to the father
	int xPos, //!< xPos to be set by tree drawing Algorithm
        yPos; //!< xPos to be set by tree drawing Algorithm

    
    //!Enumeration used for Iterative Tree Walks
	enum nodeStatus{FIRST_VISIT,
                    LEFT_VISIT ,
                    RIGHT_VISIT }
                    status;/*!< update during traversal */
    
	int modifier; //!<Used in WetherellShannon to specify proper spacing within nodes at same level, according to aesthetics
	int nodeheight; //!<Level within tree, node is present at
};


node *createNode(int InputValue,node *parent){
	node *temp;
    
	temp=(node*)malloc(sizeof(node));
    
	temp->value=InputValue;
	temp->left=NULL;
	temp->right=NULL;
	temp->father=parent;
	temp->modifier=0;
	temp->nodeheight=0;
    temp->xPos=0;
    temp->yPos=0;
    
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
        //printf("Enter the number\n");
		/*for(counter=0;counter<n;counter++)
			scanf("%d",&inputValues[counter]);
			*/
    
		node *root=treeHelper(inputValues,n);// Create Tree Using Input Values
		printf("Tree created is (inorder representation)\n");
		inorderPrint(root);

		setHeight(root,0);

		printf("\n");

		return root;
}

node *treeHelper(int inputValues[],int n){

	int counter;

	node *root=createNode(inputValues[0],NULL);
	node *current=root;

	for(counter=1;counter<n;counter++){
		current=root;
        
		while(1){ // Loop until proper position is found
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



void inorderPrint(node *root){
    /*!Also run once after tree drawing algorithms set x,y values to decide and
     assign maxX and minX values */
	if(root!=NULL){
        if(root->xPos < minX) //Update minX and maxX ( to be used in WIDTH of window)
            minX=root->xPos;
        if(root->xPos > maxX)
            maxX=root->xPos;
		inorderPrint(root->left);
		printf("Node Value  %d at (%d,%d)\n",root->value,root->xPos,root->yPos);
		inorderPrint(root->right);
	}
}

void setHeight(node *root,int height){
    
    /*!Called before Tree Drawing Algorithm to set heights of individual nodes
     and save maxHeight (which is also tree height)*/

	if(root!=NULL){
		root->nodeheight=height;
		if(height>maxHeight)
			maxHeight=height;
		setHeight(root->left,height+1);
		setHeight(root->right,height+1);
	}
}


int xCoord(node *NODE,int minX){
    return ( (NODE->xPos - minX) * 100 );
}

int yCoord(node *NODE,int WindowHeight){
    return (WindowHeight-(NODE->yPos * 50) );
}

#endif
