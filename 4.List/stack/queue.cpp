#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Queue* initQueue(){
    return createList();
}

boolean is_empty(Queue* queue){
    return is_empty(queue);
}

void push(Queue* queue, void* object){
    insertLast(queue, object);
}

void* pop(Queue* queue){
    return extract_head(queue);
}

void listQueue(Queue* queue, void (*f)(void*)){
    list(queue, f);
}

void destroyQueue(Queue* queue){
    destroy_list(queue);
}