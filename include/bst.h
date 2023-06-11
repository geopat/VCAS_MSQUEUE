#ifndef bst_h
#define bst_h

#include "vnode_bst.h"

typedef struct searchRecord{
    Vnode_bst *parent, *grandParent, *leaf;
    Update *pUpdate, *gpUpdate;
} searchRecord;


typedef struct BST
{
    Vnode_bst *Vroot;
    Camera *camera;
} BST;

BST * create_bst(Camera *cam);

searchRecord *search(BST *vroot,int key,Camera *cam);

void helpInsert(Iinfo *op,Camera *cam);

int insert_node(BST** root_vnode, int key,Camera *cam);

int delete_node(BST* root_vnode, int value,Camera *cam);
void print_tree(Vnode_bst *Vroot,Camera *cam);


#endif