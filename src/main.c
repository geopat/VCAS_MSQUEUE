#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "MSqueue.h"
#include "bst.h"

typedef struct thread_data{
    int id;
    BST **bst;
    Camera *cam;
} thread_data;

int max_threads = 10;

void *myThreadFun(void *transfer_data)
{
    thread_data *input_data = (thread_data*)transfer_data;
    for(int i = 1 ; i <= max_threads; i++){
        printf("Key = %d\n",input_data->id);
        insert_node(input_data->bst,input_data->id *max_threads+i,input_data->cam);
    }

    return NULL;
}
// 0 -> 0 1 2 3 4
// 1 -> 5 6 7 8 9

int main(){

Camera c;
c.timestamp = 0;
pthread_t thread_id[max_threads];
thread_data *input_data = malloc(sizeof(thread_data)*max_threads);

BST *bst = create_bst(&c);
print_tree(bst->Vroot,&c);

for(int i = 0 ; i< max_threads;i++){
    input_data[i].id = i;
    input_data[i].bst = &bst;
    input_data[i].cam = &c;
}

//MSqueue *QUEUE = create_queue(c);



for (int i = 0; i < max_threads; i++)
{
    pthread_create(&(thread_id[i]),NULL,myThreadFun,(void*)&(input_data[i]));
}

for (int i = 0; i < max_threads; i++)
{
    pthread_join(thread_id[i],NULL);
}


// printf("Starting INSERTING\n");
// for(int i = 0; i < 10; i++){
//     insert_node(&bst,i,&c);
//     printf("Insert done\n");
// }

print_tree(bst->Vroot,&c);


}