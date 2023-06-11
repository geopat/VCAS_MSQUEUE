#include <stdlib.h>
#include <limits.h>

#include "vnode_bst.h"

Vnode_bst *CreateVnodeBST(tree_node *val,Vnode_bst *nextv){
    Vnode_bst *tmp = malloc(sizeof(Vnode_bst));
    tmp->val = val;
    tmp->nextv = nextv;
    tmp->ts = TBD;

    return tmp;
}

tree_node *CreateTreeNode(int key){
    tree_node *tmp = malloc(sizeof(tree_node));
    tmp->key = key;
    tmp->update_record = malloc(sizeof(Update));
    tmp->update_record->info = NULL;
    tmp->update_record->st = CLEAN;
    tmp->left = CreateVnodeBST(NULL,NULL);
    tmp->right = CreateVnodeBST(NULL,NULL);
    return tmp;
}

tree_node *CreateInternalTreeNode(int key,Vnode_bst *left, Vnode_bst *right){
    tree_node *tmp = malloc(sizeof(tree_node));
    tmp->key = key;
    tmp->update_record = malloc(sizeof(Update));
    tmp->update_record->info = NULL;
    tmp->update_record->st = CLEAN;
    tmp->left = left;
    tmp->right = right;
    return tmp;
}

void destroyVnodeBST(Vnode_bst *tmp){
    free(tmp);
}

void initTSBST(Vnode_bst *curr,Camera *S){
    if(curr->ts == TBD){
        int curr_ts = S->timestamp;
        CASPTR(&(curr->ts),TBD,curr_ts);
    }
}

tree_node *vReadBST(Vnode_bst *curr,Camera *S){
    Vnode_bst *tmp = curr;
    initTSBST(tmp,S);
    return tmp->val;
}

int vCasBST(Vnode_bst **parent,Vnode_bst *old_val, tree_node *new_val,Camera *cam){
    Vnode_bst *p = *parent;
    initTSBST(p,cam);
    if(p->val != vReadBST(old_val,cam)) return FALSE;
    if(p->val == new_val) return TRUE;
    Vnode_bst *new_Vnode = CreateVnodeBST(new_val,p);
    // printf("parent %p\n",*parent);
    // printf("p = %p\n",p);
    // printf("Vnode %p\n",new_Vnode);
    if(CASPTR(parent,p,new_Vnode)){
        initTSBST(new_Vnode,cam);

        return TRUE;
    }
    else{
        destroyVnodeBST(new_Vnode);
        initTSBST(*parent,cam);
        return FALSE;
    }

}
