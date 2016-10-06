#ifndef WETHERELLSHANNON_H
#define WETHERELLSHANNON_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum AlgorithmType {NORMAL,MODIFIED}; //Implementation supports normal and modified(centered parent) version of algorithm

//Main Wetherell Shannon Loop
int generateWetherellShannon(node *root,int treeHeight,enum AlgorithmType secondPass);

//Checks whether given node is a leaf (No parents)
int isleaf(node *NODE);

//To Return minimum and maximum of two numbers
int minimum(int a, int b);
int maximum(int a, int b);

//Normal Second While loop of Wetherell Shannon
void SecondPass(node *root);

//Modified Second While loop of Wetherell Shannon
void SecondPassModified(node *root,int maxHeight);


int generateWetherellShannon(node *root,int treeHeight,enum AlgorithmType secondPass){
    int modifier[treeHeight+1]; //Modifier Array
    int nextPos[treeHeight+1]; //Next x-position available at each level
    int counter; //Loop Counter
    int place; //Provisional x-coordinate
    
    int height;// Current height being traversed
    
    int isLeaf=0;// Flag for isleaf
    
    int modifierSum;
    
    node *current;//Node being traversed
    
    //Initialize Parameters
    for(counter=0;counter<=treeHeight;counter++){
        nextPos[counter]=1;
        modifier[counter]=0;
    }
    current=root;
    current->status=FIRST_VISIT;
    
    //Preorder Walk of Tree (Node,Left,Right)
    //Generated Provisional Positioning of Tree Nodes
    //Modifier is used to remember distance to provisional place
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
                
                //Leaf : Place at next avaiable x
                //Has Left son, place to its right
                //Has Right Sone, place to its left
                //Has Both sons, place at average
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
    //Use Second Pass to cummulate modifiers and apply to each node
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
                // Cummulate Modifiers and bodily shift nodes at each levels
                // accordingly with how much previous nodes were shifted
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
//Maintains actual next position of each node
    //Maintins Minimum width while violating center over children (Aesthetic 3)
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
//Use the minimum of 3 values:
            //Next Position
            //the right of left child
            //right of father
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
