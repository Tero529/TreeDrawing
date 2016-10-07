/*! \file nAry.h
 * \brief N-ary tree creation
 
 *  The file specifies functions used to create a user input n-ary tree 
 *  which is input in preorder
 *  \n The n-ary tree node used has only one child pointer but also contains a
 *  sibling pointer, thus allowing for efficient traversals.
 *  \nNot completely robust in terms of error handling on input.
 \see WetherellShannon.h TilfordReingold.h binaryTreeTF.h binaryTreeWS.h
 */

#ifndef N_ARY_H
#define N_ARY_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "drawFunctions.h"

//!Our Node for the n-ary tree to be drawn
typedef struct nodeExt node;

//!N-Ary Tree Creator
/*!Prompts the user for number of today nodes in the tree
 * and stores it to. Following which the n-1 edges are input
 * in strictly preorder fashion.
 * \return The root of the created tree
 */
node *create();

//! Preorder Traversal of Tree
/*! Traverses the given tree in preorder by first moving along left countout
 *  and succesively traversing the node's siblings to accomplish preorder
 * before moving to a "righter" node
 *\n Preorder function also updates the minX,maxX, and maxY values 
 *  required for window WIDTH and HEIGHT creation.
*/
/*! \param t The current node being traversed
 */
void preorder(node *t);

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
int maxY=0;

int minX=200;//!< Minimum x -value of all nodes after finar positions are set , used to generate window WIDTH
int maxX=0; //!< Maximum x -value of all nodes after finar positions are set , used to generate window WIDTH

//!Our Node for the n-ary tree to be drawn
/*! The n-Ary tree is mainted with each node
 *  linked to at most one child, one sibling 
 *  and it's parent.
 */
struct nodeExt {
node *p, //!< Parent of Node
    *c,  //!< Child of Node (First Entered)
    *s, //!< Sibling of the Node
    *ce; //<! For current edge
int xcor, //!< X Coordinate of the node
    val,  //!< To be used with temporary node while taking input
    ycor, //!< Y Coordinate of the node
    mod,  //!< Modifier of Node (Offset to shift by : )
    tr;
    };


//creates the tree of variable size;
node *create(){
    node  *root=NULL,*temp,*temp1;
    
    int n, //Number of nodes
        a; //The "From node" in the input edge
    
    
    printf("input the no of nodes\n");
    scanf("%d",&n);
    
    printf("input the edges in preorder as \"parent child\" order\n");
    n--;
    
    while(n--){
        temp=(node *)malloc(sizeof(node));
        // Temporary node used for input and checking where to add it within the tree
        scanf("%d%d",&a,&(temp->val));
        
        temp->xcor=0;
        temp->ycor=0;
        temp->mod=0;
        temp->tr=0;
        temp->s=NULL;
        temp->c=NULL;
        temp->ce=NULL;
        
        if(root==NULL){//the first initailization of the root
            
            root=(node*)malloc(sizeof(node));
            root->val=a;
            root->xcor=0;
            root->ycor=1;
            root->mod=0;
            root->tr=0;
            root->p=NULL;
            root->s=NULL;
            root->c=temp;
            temp->p=root;
            temp->ycor=2;
            temp1=temp;
            root->ce=temp;
        }
        else{
            while(1){
                if(temp1->val==a){//when the current edge is for the
                    if(temp1->c==NULL){//when there is no child currently
                        temp1->c=temp;
                    temp1->ce=temp;
                    temp->p=temp1;
                    temp->ycor=temp->p->ycor+1;
                    temp1=temp;
                }else{//when the node has a child already
                    (temp1->ce)->s=temp;
                    temp->p=temp1;
                    temp1->ce=temp;
                    temp->ycor=temp->p->ycor+1;
                    temp1=temp;
                }
            break;
            }else{
                temp1=temp1->p;
            }
        }
    }
}
return root;
}

//prints the preorder of the nodes
void preorder(node *t){
    
    if(t!=NULL){
    // Check and Update extreme x and y values needed for window creation
        if(minX>t->xcor)
            minX=t->xcor;
        if(maxX<t->xcor)
            maxX=t->xcor;
        if(maxY<t->ycor)
            maxY=t->ycor;
           
        printf("(%d ,%d)\n",t->xcor,t->ycor);
        t=t->c;
        
        while(t!=NULL){ // Visit all siblings at current level before going back a level
            preorder(t);
            t=t->s;
        }
    }
}



int xCoord(node *NODE,int minX){
    return ( (NODE->xcor - minX) * 50 );
}

int yCoord(node *NODE,int WindowHeight){
    return (WindowHeight-((2*(NODE->ycor -1)+1) * 50) );
}

#endif
