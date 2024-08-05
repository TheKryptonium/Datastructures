#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include "table.h"

static char* toChar(Object* object){
    return (char*)object;
}

static int compareCar(Object* object, Object* object2){
    return strcmp(toChar(object), toChar(object2));
}

Table* createTable(int max, char* (*toString)(Object*), int (*toCompare)(Object*, Object*)){
    Table* table = new Table();
    table->max=max;
    table->length=0;
    table->elements=(Object**)malloc(sizeof(Object*)*max);
    table->toString=toString;
    table->toCompare=toCompare;
    return table;
}

Table* createTable(int max){
    return createTable(max, toChar, compareCar);
}

void destroyTable(Table* table){
    free(table->elements);
    free(table);
}

boolean insertTable(Table* table, Object* object){
    if(table->length<table->max){
        table->elements[table->length++]=object;
        return True;
    }else{
        return False;
    }
} 

int Length(Table* table){
    return table->length;
}

Object* locateElement(Table* table, int position){
    return (position > 0 && position < table->length)? table->elements[position]:NULL;
}

Object* sequentialAccess(Table* table, Object* search){
    int i=0;
    boolean found =False;
    while(i<table->length && !found){
        found=table->toCompare(search, table->elements[i]);
        if(!found) i++;
    }
    return (found)?table->elements[i]:NULL;
}

Object* dichotomy(Table* table, Object* search, int left, int right){
    Object* result;
    if(left<=right){
        int middle = (left+right)/2;
        int c = table->toCompare(search, table->elements[middle]);
        if(c==0){
            result=table->elements[middle];
        }else if(c>0){
            result=dichotomy(table, search, middle+1,right);
        }else{
            result=dichotomy(table, search, left, middle-1);
        }
    }else{
        result=NULL;
    }
    return result;
}

Object* dichotomy(Table* table, Object* search){
    return dichotomy(table, search, 0, table->length-1);
}

static void swap(Table* table, int n1, int n2){
    Object* temp=table->elements[n1];
    table->elements[n1]=table->elements[n2];
    table->elements[n2]=temp;
}

void sort(Table* table){
    int length=Length(table);
    for(int i=0; i<length-1; i++){
        for(int j=length-1; j>i;j--){
            Object* object1 = locateElement(table,j-1);
            Object* object2 = locateElement(table,j);
            if(table->toCompare(object1, object2)>0){
                swap(table,j-1,j);
            }
        }
    }
}


void listTable(Table* table){
    for(int i=0; i<Length(table); i++){
        printf("%s\n", table->toString(table->elements[i]));
    }
}