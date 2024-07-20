#ifndef STACK_H
#define STACK_H

#include "..\list.h"

typedef List Stack;

Stack* createStack();
boolean is_empty(Stack* sta);
void stackin(Stack* sta, void* object);
void* stackout(Stack* sta);
void listStack(Stack* sta, void (*f)(void*));
void destroyStack(Stack* sta);

#endif