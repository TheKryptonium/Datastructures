#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablehcc.h"

static char* toChar(Object* object){
    return (char*)object;
}

static int toCompare(Object* object1, Object* object2){
    return strcmp(toChar(object1),toChar(object2));
}

TableHCC* createTableHCC(int max, char* (*toString)(Object*), int (*toCompare)(Object*, Object*), int (*hashcode)(Object*, int), int (*resolution)(int, int, int)){
    TableHCC* table =new TableHCC();
    table->max=max;
    table->length=0;
    table->elements = (tableElement*)malloc(sizeof(tableElement)*max);
    table->toString=toString;
    table->toCompare=toCompare;
    table->hashcode=hashcode;
    table->resolution=resolution;
    for(int j=0; j<max;j++){
        table->elements[j].object=NULL;
        table->elements[j].next=NILE;
    }
}

TableHCC* createTableHCC(int max){
    return createTableHCC(max,toChar,toCompare,hash1,resolution1);
}

Object* lookFor(TableHCC* table, Object* object){
    boolean found = False;
    int h = table->hashcode(object, table->max);
    int re = h;
    while(!found && re!=NILE){
        found = table->toCompare(object,table->elements[re].object)==0;
        if(!found) re = table->elements[re].next;
    }
    return re==NILE? NULL: table->elements[re].object;
}