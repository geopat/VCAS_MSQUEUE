#ifndef msqueue_h
#define msqueue_h

#include "vnode.h"

typedef struct MSqueue
{
    Vnode *head;
    Vnode *tail;
    Camera *camera;
} MSqueue;

MSqueue * create_queue(Camera *cam);

void enqueue(MSqueue* QUEUE, int value,Camera *cam);

int dequeue(MSqueue* QUEUE, int *value,Camera *cam);

#endif