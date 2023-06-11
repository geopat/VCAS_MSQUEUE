#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "bst.h"
#include "globals.h"

BST * create_bst(Camera *cam){

    //Creating Tree
    BST *tree = malloc(sizeof(BST));
    tree->camera = cam;
    //Inserting root Node Inf1
    tree_node *inf1 = CreateTreeNode(INFINITY(1));
    tree_node *inf0 = CreateTreeNode(INFINITY(0));
    tree_node *inf2 = CreateTreeNode(INFINITY(2));
    tree->Vroot = CreateVnodeBST(inf1,NULL);
    tree_node *root = vReadBST(tree->Vroot,cam);

    Vnode_bst *Vinf0 = CreateVnodeBST(inf0,root->right);
    Vnode_bst *Vinf2 = CreateVnodeBST(inf2,root->left);

    root->left = Vinf2;
    root->right = Vinf0;

    return tree;
}

int isLeaf(Vnode_bst *tmp,Camera *cam){
    tree_node *tn = vReadBST(tmp,cam);
    if(tn == NULL) return FALSE;
    if(vReadBST(tn->left,cam) == NULL && vReadBST(tn->right,cam) == NULL){
        return TRUE;
    }
    return FALSE;
}


searchRecord * search(BST *tree,int key,Camera *cam){
    Vnode_bst *gp = NULL, *p =NULL;
    Vnode_bst *l = tree->Vroot;
    Update *gpUpdate = NULL, *pUpdate = NULL;
    
    //while l->val != NULL
    tree_node *lVal = vReadBST(l,cam);
    while(!isLeaf(l,cam)){
        gp = p;
        p = l;
        gpUpdate = pUpdate;
        pUpdate = vReadBST(p,cam)->update_record;

        if(key < lVal->key){
            l = lVal->left;
            lVal = vReadBST(l,cam);
        }
        else{
            l = lVal->right;
            lVal = vReadBST(l,cam);
        }
        
    }
    searchRecord *tmp = malloc(sizeof(searchRecord));
    tmp->leaf = l;
    tmp->parent = p;
    tmp->grandParent = gp;
    tmp->pUpdate = pUpdate;
    tmp->gpUpdate = gpUpdate;

    return tmp;
}

void helpInsert(Iinfo *op,Camera *cam){
    // printf("Key =  %d \n ",op->new_internal->key);
    // printf("Parent key %p --> %d\n",vReadBST(op->parent,cam)->key,op->parent->val->key);
    // printf("op->leaf %p --> val %d\n",op->leaf,op->leaf->val->key);
    if(op->new_internal->key < vReadBST(op->parent,cam)->key){
        //printf("op->parent->val->left %p --> val %d\n",op->parent->val->left,op->parent->val->left->val->key);

        vCasBST(&op->parent->val->left,op->leaf,op->new_internal,cam);
        //printf("op->parent = %p\n",op->parent->val->left);
    }
    else{
        vCasBST(&op->parent->val->right,op->leaf,op->new_internal,cam);
    }
    Update *curr = op->parent->val->update_record;
    if(curr->st == IFLAG){
        if(curr->info == op){
            CASPTR(&op->parent->val->update_record->st,curr->st,CLEAN);
        }
    }
}

int insert_node(BST** root_vnode, int key,Camera *cam){
    Vnode_bst *newSibling;

    while(TRUE){
        searchRecord *tmp = search(*root_vnode,key,cam);
        printf("------------------------------------------------\n");
        printf("Search Record\n");
        printf("Parent = %d\n",tmp->parent->val->key);
        printf("Leaf = %d\n",tmp->leaf->val->key);
        printf("pUPDATE state = %d\n",tmp->pUpdate->st);
        printf("------------------------------------------------\n");

        if(vReadBST(tmp->leaf,cam)->key == key) return FALSE;
        if(tmp->pUpdate->st != CLEAN){printf("Implement HELP needed\n"); return FALSE;}//HELP(tmp->pUpdate);
        else{
                //Creating new Node
                tree_node *new_node = CreateTreeNode(key);
                Vnode_bst *new_vnode = CreateVnodeBST(new_node,NULL);
                //Creating new vnode for old leaf node
                newSibling = CreateVnodeBST(vReadBST(tmp->leaf,cam),NULL);
                // printf("New Sibling Vnode %p\n",newSibling);
                // printf("New Sibling->val  %p --> %d\n",newSibling->val,newSibling->val->key);

                //Create new Internal
                tree_node * internal = NULL;
                if(key < vReadBST(tmp->leaf,cam)->key){
                    internal = CreateInternalTreeNode(vReadBST(tmp->leaf,cam)->key,new_vnode,newSibling);
                }
                else{
                    internal = CreateInternalTreeNode(key,newSibling,new_vnode);
                }
                // printf("Internal->val  %p-->%d\n",internal,internal->key);
                // printf("Internal left vnode  %p\n",internal->left);
                // printf("Internal left->val = %p--> %d\n",internal->left->val,internal->left->val->key); 
                // printf("Internal right vnode  %p\n",internal->right);
                // printf("Internal left->val = %p--> %d\n",internal->right->val,internal->right->val->key); 


                Iinfo *op = malloc(sizeof(Iinfo));
                op->leaf = tmp->leaf;
                op->parent = tmp->parent;
                op->new_internal = internal;
                Update *up = malloc(sizeof(Update));
                up->st = IFLAG;
                up->info = op;
                if(CASPTR(&(vReadBST(tmp->parent,cam)->update_record),tmp->pUpdate,up)){
                    printf("Help insert\n");
                    helpInsert(op,cam);
                }
                return TRUE;
        }
    }
}

void print_tree(Vnode_bst *Vroot,Camera *cam){
    Vnode_bst *curr = Vroot;
    if(curr->val == NULL) return;

    print_tree(curr->val->left,cam);
    if(isLeaf(curr,cam)){
        printf("%d\n",curr->val->key);
    }
    print_tree(curr->val->right,cam);

    
    
}