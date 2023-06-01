#include <stdlib.h>
#include <limits.h>
#include "MSqueue.h"
#include "globals.h"

MSqueue *create_queue(Camera *cam){

    /*Creating Sentinel node*/
    Node *sentinel = malloc(sizeof(Node));
    sentinel->next = CreateVnode(NULL,NULL);
    sentinel->value = BOT;

    MSqueue *queue = malloc(sizeof(MSqueue));
    queue->head = CreateVnode(sentinel,NULL);
    queue->tail = CreateVnode(sentinel,NULL);
    queue->camera = cam;

    return queue;
}


void enqueue(MSqueue* QUEUE, int value,Camera *cam){

    /*Creating Node to be added
    
    -----------------------------------------
    |int| Vnode*|     |Node | int   | Vnode*|
    -------------     -----------------------
    |val| next -|---> | nil |  ts   | nil   |
    -------------     ----------------------- 
    
    */
    Node *tmp = malloc(sizeof(Node));
    tmp->value = value;
    tmp->next = CreateVnode(NULL,NULL);
    Node *last;

    while(TRUE){
        last = vRead(QUEUE->tail,cam);
        Vnode *next = last->next->nextv;

        if(last == vRead(QUEUE->tail,cam)){
            if(next == NULL){
                if(vCas(&QUEUE->tail,last,tmp,cam,0))//Changing pointer of last item point to Vnode of inserting item
                    break;
            }
            else{
                exit(0);
                vCas(&QUEUE->tail,last,vRead(next,cam),cam,1);

            }
        }
    }
    vCas(&QUEUE->tail,last,tmp,cam,1);
}

int dequeue(MSqueue* QUEUE,int *value,Camera *cam){

    while(TRUE){
        Node *first = vRead(QUEUE->head,cam);
        Node *last = vRead(QUEUE->tail,cam);
        Node *next = vRead(first->next,cam);
        

        if(first == vRead(QUEUE->head,cam)){
            if(first == last){
                if(next ==NULL){
                    return FALSE;
                }
                vCas(&QUEUE->tail,last,next,cam,1);//tail is falling behind try advance
            }
            else{
                *value = next->value;
                if(vCas(&QUEUE->head,first,next,cam,1))
                    break;
            }
        }
    }

  return TRUE;

}

