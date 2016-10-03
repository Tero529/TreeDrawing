#ifndef WETHERELLSHANNON_H
#define WETHERELLSHANNON_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum AlgorithmType {NORMAL,MODIFIED};
int generateWetherellShannon(node *root,int treeHeight,enum AlgorithmType secondPass);

int isleaf(node *NODE);
int minimum(int a, int b);
int maximum(int a, int b);
void SecondPass(node *root);
void SecondPassModified(node *root,int maxHeight);


int generateWetherellShannon(node *root,int treeHeight,enum AlgorithmType secondPass){
  int modifier[treeHeight+1];
    int nextPos[treeHeight+1];
    int counter;
  int place;
  int height;
  int isLeaf=0;
  int modifierSum;
  node *current;

  for(counter=0;counter<=treeHeight;counter++){
    nextPos[counter]=1;
    modifier[counter]=0;
  }
  current=root;
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
                      else if (current->left==NULL)
                        place=( (current->right)->xPos ) - 1;
                      else if (current->right==NULL)
                        place=( (current->left)->xPos ) + 1;
                      else
                        place=( (current->left)->xPos + (current->right)->xPos)/2;

                      modifier[height]=maximum(modifier[height],nextPos[height]-place);

                      if(isLeaf)
                        current->xPos=place;
                      else
                        current->xPos=place +modifier[height];

                      nextPos[height]=current->xPos+2;
                      current->modifier=modifier[height];
                      current=current->father;

                      break;
    }
  }
  if(secondPass==NORMAL)
    SecondPass(root);
  else
    SecondPassModified(root,maxHeight);
  return 1;
}

void SecondPass(node *root){

    node *current=root;
    current->status=FIRST_VISIT;
    int modifierSum=0;
    while(current !=NULL){

      switch(current->status){
        case FIRST_VISIT:
                          current->xPos=current->xPos+modifierSum;
                          modifierSum=modifierSum + current->modifier;
                          current->yPos=2*current->nodeheight+1;
                          current->status=LEFT_VISIT;
                          if(current->left !=NULL){
                            current=current->left;
                            current->status=FIRST_VISIT;
                          }
                          break;
        case LEFT_VISIT:
                        current->status=RIGHT_VISIT;
                        if(current->right!=NULL){
                          current=current->right;
                          current->status=FIRST_VISIT;
                        }
                        break;
        case RIGHT_VISIT:
                          modifierSum= modifierSum - current->modifier;
                          current=current->father;
                          break;
      }

    }

}

void SecondPassModified(node *root,int maxHeight){

  node *current=root;
  current->status=FIRST_VISIT;
  int modifierSum=0;
  int nextPos[maxHeight+1];

  int counter=0;
  for(counter=0;counter<=maxHeight;counter++)
    nextPos[counter]=1;

  while(current !=NULL){

    switch(current->status){
      case FIRST_VISIT:
                        modifierSum=modifierSum + current->modifier;
                        current->status=LEFT_VISIT;
                        if(current->left !=NULL){
                          current=current->left;
                          current->status=FIRST_VISIT;
                        }
                        break;
      case LEFT_VISIT:
                      current->xPos=minimum(nextPos[current->nodeheight], current->xPos + modifierSum - current->modifier);
                      if(current->left !=NULL)

                        current->xPos=maximum(current->xPos,current->left->xPos + 1);

                      if(current->father!=NULL){
                        if(current->father->status == RIGHT_VISIT)
                          current->xPos=maximum(current->xPos,current->father->xPos +1);
                      }

                      nextPos[current->nodeheight]=current->xPos +2;
                      current->yPos=2*current->nodeheight + 1;
                      current->status=RIGHT_VISIT;
                      if(current->right!=NULL){
                        current=current->right;
                        current->status=FIRST_VISIT;
                      }
                      break;
      case RIGHT_VISIT:
                        modifierSum= modifierSum - current->modifier;
                        current=current->father;
                        break;
    }

  }

}

int isleaf(node *NODE){
  if ((NODE->left == NULL) && (NODE->right == NULL))
      return 1;
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
