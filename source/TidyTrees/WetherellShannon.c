#ifndef WETHERELLSHANNON_H
#define WETHERELLSHANNON_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int isleaf(node *NODE);
int minimum(int a, int b);
int maximum(int a, int b);

int generateWetherellShannon(node *root,int treeHeight){
  int modifier[treeHeight];
	int nextPos[treeHeight];
	int counter;
  int place;
  int height;
  int isLeaf=0;
  int modifierSum;
  node *current;

  for(counter=0;counter<treeHeight;counter++){
    nextPos[counter]=1;
    modifier[counter]=0;
  }

  current=root;
  printf("%d\n",current->value);
  current->status=FIRST_VISIT;

  while(current != NULL){

    switch(current->status){
      case FIRST_VISIT:
                      current->status=LEFT_VISIT;
                      if(current->left !=NULL){
                        current=current->left;
                        current->status=FIRST_VISIT;
                      }
                      break;

      case LEFT_VISIT:
                      current->status=RIGHT_VISIT;
                      if(current->right !=NULL){
                        current=current->right;
                        current->status=FIRST_VISIT;
                      }
                      break;

      case RIGHT_VISIT:
                      height=current->nodeheight;
                      isLeaf=isleaf(current);
                      if(isLeaf)
                        place=nextPos[height];
                      else if (current->left!=NULL)
                        place=( (current->right)->xPos ) - 1;
                      else if (current->right!=NULL)
                        place=( (current->left)->xPos ) + 1;
                      else
                        place=( (current->left)->xPos + (current->left)->xPos)/2;

                      modifier[height]=maximum(modifier[height],nextPos[height]-place);

                      if(isLeaf)
                        current->xPos=place;
                      else
                        current->xPos=place +modifier[height];

                      nextPos[height]=current->xPos+2;
                      printf("Current Value is %d %d \n",current->value,current->xPos);

                      current->modifier=modifier[height];
                      current=current->father;

                      break;
    }
  }
  return 1;
}

int isleaf(node *NODE){
  return ((NODE->left == NULL) && (NODE->right == NULL));
}

int maximum(int a,int b){
  if(a>b)
    return a;
  else
    return b;
}
int minimum(int a, int b){
  if(a>b)
    return b;
  else
    return a;
}

#endif
