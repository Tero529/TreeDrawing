#ifndef BINARYTREE_H
#define BINARYTREE_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct nodet node; //node used to refer to a node in the binary tree

/* The maximum y-value amongs all nodes after the tree drawing algorithm is
run */
int maxHeight=0;
/* The minimum and maximum x-values of the nodes after the tree drawing
algorihtm, It is used to calculate the width of the subsequently created window */
int minX=0;
int maxX=0;

/*A function to allocate space for a fresh node, initilise its
attributes and return the pointer to it */
node *createNode(int InputValue,node *parent);

/*Creates a Binary Search Tree using the number of nodes and values of those
nodes as specified within in */
node *createTree(void);

/* Works from within the createTree() function to find correct position for
the next node*/
node *treeHelper(int inputValues[],int n);

/* Prints the created tree in inorder representation and also assigns maxX , minX ,
and maxHeight */
void inorderPrint(node *root);

/* Sets the level(height) of each node, which is used in the subsequent tree
drawing algorithms */
void setHeight(node *root,int height);

/*returns the x-xoordinate and y-coordinate of a given node for drawing,
they are scaled and offset to fit within the window */
int xCoord(node *NODE,int minX);
int yCoord(node *NODE,int WindowHeight);

/*The node structure of a node within the tree */
struct nodet{
	int value; //Data in the node
	node *left,*right,*father; // Pointers to left son, right son and parent of the node
	int xPos,yPos; // the drawing position to be set by tree drawing algorithms
	enum nodeStatus{FIRST_VISIT , LEFT_VISIT , RIGHT_VISIT } status; //Status field used to iterative tree walks
	int modifier; //Used in WetherellShannon to specify proper spacing within nodes at same level, according to aesthetics
	int nodeheight; //Level within tree, node is present at
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
		/*for(counter=0;counter<n;counter++)
			scanf("%d",&inputValues[counter]);
			*/
		node *root=treeHelper(inputValues,n);
		printf("Tree created is (inorder representation)\n");
		inorderPrint(root);

		setHeight(root,0);//Set nodeheight field of each node in final tree

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

// Prints in -order representation of the tree entered

/*Also run once after tree drawing algorithms set x,y values to decide and
assign maxX and minX values */

void inorderPrint(node *root){
	if(root!=NULL){
        if(root->xPos < minX)
            minX=root->xPos;
        if(root->xPos > maxX)
            maxX=root->xPos;
		inorderPrint(root->left);
		printf("Node Value  %d at (%d,%d)\n",root->value,root->xPos,root->yPos);
		inorderPrint(root->right);
	}
}

/*Called before Tree Drawing Algorithm to set heights of individual nodes
and save maxHeight (which is also tree height)*/

void setHeight(node *root,int height){
	if(root!=NULL){
		root->nodeheight=height;
		if(height>maxHeight)
			maxHeight=height;
		setHeight(root->left,height+1);
		setHeight(root->right,height+1);
	}
}

/*Each integral coordinate is scaled by 100 to be visible appropriately
in the screen (screen is typically 800x600 or greater), and is off set on the
left by 50 pixels (as node radius  drawn is 25 pixels)*/

int xCoord(node *NODE,int minX){
    return ( (NODE->xPos - minX) * 100 );
}

/* Open GL (0,0) Refers to botom left corner while algorithm refers to the same
as the top right corner, hence , node's y value is subtracted from HEIGHT of
window to set appropriate OpenGL drawing point*/

int yCoord(node *NODE,int WindowHeight){
    return (WindowHeight-(NODE->yPos * 50) );
}

#endif
