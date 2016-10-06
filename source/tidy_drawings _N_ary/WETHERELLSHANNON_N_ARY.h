#ifndef WETHERELLSHANNON_N_ARY_H
#define WETHERELLSHANNON_N_ARY_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
Each node contains links to
p:-parent
c:-child
s:-sibling

*/
typedef struct nodes {
struct nodes *p,*c,*s,*ce;
int val,xcor,ycor,mod,tr;
    int status;
}node;

//creates the tree of variable size;

node* create (){
node  *root=NULL,*temp,*temp1;
int n,a,b;
printf("input the no of nodes\n");
scanf("%d",&n);
printf("input the edges in preorder  parent and child order\n");
n--;
while(n--){
    temp=(node *)malloc(sizeof(node));
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
    }else{
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
    node *temp;
    if(t!=NULL){
        printf("%(d ,%d)\n",t->xcor,t->ycor);
        t=t->c;
        while(t!=NULL){
            preorder(t);
            t=t->s;
        }
    }
}
#endif
