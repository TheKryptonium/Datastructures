#ifndef QUEUE_H
#define QUEUE_H
#include "..\list.h"

typedef List Queue;

Queue* initQueue();
boolean is_empty(Queue* queue);
void push(Queue* queue, void* objet);
void* pop(Queue* queue);
void listQueue(Queue* queue, void (*f)(void*));
void destroyQueue(Queue* queue);

#endif