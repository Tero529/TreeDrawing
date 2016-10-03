
#ifndef TILFORDREINGOLD_H
#define TILFORDREINGOLD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binaryTreeTR.h"

#define minsep 4
typedef struct extremepoints extr;

void generateTilfordReingold(node *root);
void ofset(node *t,int level,extr *rmost,extr *lmost);
void createPos(node *t,int xpos);

struct extremepoints{
    node * addr;
    int off,lev;
};

void generateTilfordReingold(node *root){
    extr rightMost,leftMost;
    ofset(root,1,&rightMost,&leftMost);
    createPos(root,10);
}

void ofset(node *t,int level,extr *rmost,extr *lmost){
    node *l,*r;
    extr lr,ll,rr,rl;
    int cursep,rootsep,loffsum,roffsum;
    if(t==NULL){
        lmost->lev=-1;
        rmost->lev=-1;
    }else{
        t->yPos=level;
        l=t->left;
        r=t->right;
        ofset(l,level+1,&lr,&ll);
        ofset(r,level+1,&rr,&rl);
        if (r==NULL&&l==NULL){
            rmost->addr=t;
            lmost->addr=t;
            rmost->lev=level;
            lmost->lev=level;
            rmost->off=0;
            lmost->off=0;
            t->offset=0;
        }else{
            cursep=minsep;
            rootsep=minsep;
            loffsum=0;
            roffsum=0;
            while(l!=NULL&&r!=NULL){
                if(cursep<minsep){
                    rootsep=rootsep+(minsep-cursep);
                    cursep=minsep;
                }
                if(l->right!=NULL){
                    loffsum=loffsum+l->offset;
                    cursep=cursep-l->offset;
                    l=l->right;
                }else{
                    loffsum=loffsum-l->offset;
                    cursep=cursep+l->offset;
                    l=l->left;
                }
                if(r->left!=NULL){
                    roffsum=roffsum-r->offset;
                    cursep=cursep-r->offset;
                    r=r->left;
                }else{
                    roffsum=roffsum+r->offset;
                    cursep=cursep+r->offset;
                    r=r->right;
                }
            }
            t->offset=(rootsep+1)/2;
            loffsum-=t->offset;
            roffsum+=t->offset;
            if(rl.lev>ll.lev||t->left==NULL){
                *lmost=rl;
                lmost->off+=t->offset;
            }else{
                *lmost=ll;
                lmost->off-=t->offset;
            }
            if(lr.lev>rr.lev||t->right==NULL){
                *rmost=lr;
                rmost->off+=t->offset;
            }else{
                *rmost=rr;
                rmost->off-=t->offset;
            }
            if(l!=NULL&&l!=t->left){
                (rr.addr)->thread=1;
                (rr.addr)->offset=abs(rr.off+t->offset-loffsum);
                if(loffsum-t->offset<=rr.off){
                    (rr.addr)->left=l;
                }else{
                    (rr.addr)->right=l;
                }
            }else if(r!=NULL&&r!=t->right){
                (ll.addr)->thread=1;
                (ll.addr)->offset=abs(ll.off+t->offset-roffsum);
                if(roffsum-t->offset>=ll.off){
                    (ll.addr)->right=r;
                }else{
                    (ll.addr)->left=r;
                }
            }
            
            
        }
    }
}



void createPos(node *t,int xpos){
    if (t!=NULL){
        t->xPos=xpos;
        if(t->thread==1){
            t->thread=0;
            t->left=NULL;
            t->right=NULL;
        }
        createPos(t->left,xpos-t->offset);
        createPos(t->right,xpos+t->offset);
    }
}


#endif

