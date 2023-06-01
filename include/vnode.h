#ifndef vnode_h
#define vnode_h


typedef struct Vnode Vnode;

typedef struct Camera{
    int timestamp;
}Camera;

typedef struct Node{
    int value;
    Vnode *next;
} Node;

typedef struct Vnode {
    Node *val;
    struct Vnode *nextv;
    int ts;
}Vnode;

Vnode *CreateVnode(Node *val,Vnode *nextv);

void destroyVnode(Vnode *vn);

void initTS(Vnode *n, Camera *S);

Node *vRead(Vnode *curr,Camera *S);

int vCas(Vnode **Vfirst, Node *old_val, Node *new_val,Camera *cam,int mode);

#endif
