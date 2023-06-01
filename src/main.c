#include <stdio.h>
#include <stdlib.h>
#include "MSqueue.h"


int main(){

Camera *c = malloc(sizeof(Camera));
c->timestamp = 0;

MSqueue *QUEUE = create_queue(c);

for(int i = 0; i < 10; i++){
    enqueue(QUEUE,i,QUEUE->camera);
    printf("Enqueu done\n");
}

for(int i = 0; i < 10; i++){
    int j = 0 ;
    dequeue(QUEUE,&j,QUEUE->camera);
    printf("Value = %d\n",j);
}


}