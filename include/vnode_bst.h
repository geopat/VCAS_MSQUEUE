#ifndef vnode_bst_h
#define vnode_bst_h

#include "globals.h"

typedef struct Vnode_bst Vnode_bst;
typedef struct tree_node tree_node;

enum State{CLEAN,IFLAG};

typedef struct Iinfo{
    Vnode_bst *parent;
    tree_node *new_internal;
    Vnode_bst *leaf;
} Iinfo;

typedef struct Update {
    enum State st;
    Iinfo *info;
} Update;

typedef struct tree_node{
    Vnode_bst *left;
    Vnode_bst *right;
    int key;
    Update *update_record;
} tree_node;

typedef struct Vnode_bst {
    tree_node *val;
    struct Vnode_bst *nextv;
    int ts;
} Vnode_bst;

tree_node *CreateTreeNode(int key);
tree_node *CreateInternalTreeNode(int key,Vnode_bst *left, Vnode_bst *right);


Vnode_bst *CreateVnodeBST(tree_node *val,Vnode_bst *nextv);

void destroyVnodeBST(Vnode_bst *vn);

void initTSBST(Vnode_bst *n, Camera *S);

tree_node *vReadBST(Vnode_bst *curr,Camera *S);

int vCasBST(Vnode_bst **parent,Vnode_bst *old_val, tree_node *new_val,Camera *cam);

#endif
