#ifndef BINARYTREE_H
#define BINARYTREE_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct nodet node;
int maxHeight=0;
int minX=0;
int maxX=0;

node *createNode(int InputValue,node *parent);
node *createTree(void);
node *treeHelper(int inputValues[],int n);
void inorderPrint(node *root);
void setHeight(node *root,int height);
int xCoord(node *NODE);
int yCoord(node *NODE,int WindowHeight);

struct nodet{
	int value;
	node *left,*right,*father;
	int xPos,yPos;
	enum nodeStatus{FIRST_VISIT , LEFT_VISIT , RIGHT_VISIT } status;
	int modifier;
	int nodeheight;
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
		printf("How many values? ");
		//scanf("%d",&n);
		n=11;
		int inputValues[]={7,4,12,2,6,9,15,1,3,8,25};
		int counter=0;
		/*for(counter=0;counter<n;counter++)
			scanf("%d",&inputValues[counter]);
			*/
		node *root=treeHelper(inputValues,n);
		printf("Tree created is (inorder representation)\n");
		inorderPrint(root);
		setHeight(root,0);
		printf("\n");
		return root;
}

node *treeHelper(int inputValues[],int n){
	int flag=0;
	int counter;
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

void setHeight(node *root,int height){
	if(root!=NULL){
		root->nodeheight=height;
		if(height>maxHeight)
			maxHeight=height;
		setHeight(root->left,height+1);
		setHeight(root->right,height+1);
	}
}

int xCoord(node *NODE){
    return ( (NODE->xPos) * 100 -200*minX);
}
int yCoord(node *NODE,int WindowHeight){
    return (WindowHeight-(NODE->yPos * 100) );
}

#endif
