#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack* createStack(){
    return createList();
}

boolean is_empty(Stack* sta){
    return (sta->head==NULL)?True:False;
}

void stackin(Stack* sta, void* object){
    insertHead(sta, object);
}

void* stackout(Stack* sta){
   return (is_empty(sta))? NULL:extract_head(sta);
}

void listStack(Stack* sta,void (*f)(void*)){
    list(sta, f);
}

void destroyStack(Stack* sta){
    destroy_list(sta);
}