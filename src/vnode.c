#include <stdlib.h>
#include <limits.h>
#include "vnode.h"
#include "globals.h"

Vnode *CreateVnode(Node *val,Vnode *nextv){
    Vnode *tmp = malloc(sizeof(Vnode));
    tmp->val = val;
    tmp->nextv = nextv;
    tmp->ts = TBD;

    return tmp;
}

void destroyVnode(Vnode *vn){
    free(vn);
}


void initTS(Vnode *curr,Camera *S){
    if(curr->ts == TBD){
        int curr_ts = S->timestamp;
        CASPTR(&(curr->ts),TBD,curr_ts);
    }
}

Node *vRead(Vnode *curr,Camera *S){
    Vnode *tmp = curr;
    initTS(tmp,S);
    return tmp->val;
}

int vCas(Vnode **Vfirst, Node *old_val, Node *new_val,Camera *cam,int mode){
    
    Vnode* curr = *Vfirst;
    initTS(curr,cam);
    if(curr->val != old_val) return FALSE;
    if(new_val == old_val) return TRUE;

    //Changing pointer of last item point to Vnode of inserting item
    if(mode == 0){
        curr = (*Vfirst)->val->next;

        Vnode *newVN = CreateVnode(new_val,curr);

        if(CASPTR(&(*Vfirst)->val->next,curr,newVN)){
            initTS(newVN,cam);
            return TRUE;
        }
        else{

            destroyVnode(newVN);
            initTS((*Vfirst)->val->next,cam);
            return FALSE;
        }
    }
    else{ //Changing Head of QUEUE point to new vNode pointer 

        Vnode *newVN = CreateVnode(new_val,curr);

        if(CASPTR(&(*Vfirst),curr,newVN)){
            initTS(newVN,cam);
            return TRUE;
        }
        else{
            destroyVnode(newVN);
            initTS((*Vfirst),cam);
            return FALSE;
        }
    }
}


