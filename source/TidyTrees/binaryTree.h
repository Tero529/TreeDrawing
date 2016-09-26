#ifndef BINARYTREE_H
#define BINARYTREE_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct nodet node;

node *createNode(int InputValue,node *parent);
node *createTree(void);
node *treeHelper(int inputValues[],int n);
int getHeight(node *root);
void inorder(node *root);


struct nodet{
	int value;
	node *left,*right,*father;
	int xPos,yPos;
	int status;
	int modifier;
};

node *createNode(int InputValue,node *parent){
	node *temp;
	temp=(node*)malloc(sizeof(node));
	temp->value=InputValue;
	temp->left=NULL;
	temp->right=NULL;
	temp->father=parent;
	temp->modifier=0;
	return temp;
}

node *createTree(void){
		int n;
		printf("How many values? ");
		scanf("%d",&n);
		int inputValues[n];
		int counter=0;
		for(counter=0;counter<n;counter++)
			scanf("%d",&inputValues[counter]);
		node *root=treeHelper(inputValues,n);
		printf("Tree created is (inorder representation)\n");
		inorder(root);
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

void inorder(node *root){
	if(root!=NULL){
		inorder(root->left);
		printf("%d ",root->value);
		inorder(root->right);
	}
}
#endif
