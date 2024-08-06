#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablehc.h"


static char* toChar(Object* object){
    return (char*)object;
}

static int toCompare(Object* object1, Object* object2){
    return strcmp(toChar(object1), toChar(object2));
}

TableHC* createTableHC(int max, char* (*toString)(Object*), int (*toCompare)(Object*, Object*), int (*hashcode)(Object*, int), int (*resolution)(int,int, int)){
    TableHC* table = new TableHC();
    table->max=max;
    table->length=0;
    table->elements=(Object**)malloc(sizeof(Object*)*max);
    table->toString=toString;
    table->toCompare=toCompare;
    table->hashcode=hashcode;
    table->resolution=resolution;
    return table;
}

TableHC* createTableHC(int max){
    return createTableHC(max, toChar, toCompare, hash1, resolution1);
}

static int resolution(TableHC* table, int h){
    boolean found=False;
    int i=1;
    int re;
    initRand(table->max);

    while((i<table->max) && (!found)){
        re=table->resolution(h, table->max, i);
        found=table->elements[re]==NULL;
        i++;
    }
    if(!found) re=-1;
    return re;
}

boolean appendHC(TableHC* table, Object* object){
    int h=table->hashcode(object, table->max);
    if(table->elements[h]==NULL){
        table->elements[h]=object;
    }else{
        int re = resolution(table, h);
        if(re!=-1){
            table->elements[re]=object;
        }else{
            printf("The table is full!");
            return False;
        }
   }
   table->length++;
   return True; 
}

Object* lookFor(TableHC* table, Object* object){
    boolean found=False;
    int h = table->hashcode(object, table->max);
    int re=h;
    int i=1;
    while(!found && re!=-1){
        if(table->elements[re]==NULL){
            re=-1;
        }else{
            found=table->toCompare(object, table->elements[re])==0;
            if(!found) re = table->resolution(h,table->max,i++);
        }
    }
    return re==-1? NULL:table->elements[re];
}

void listHC(TableHC* table){
    int sn=0;
    for(int j=0; j<table->max;j++){
        if(table->elements[j]!=NULL){
            printf("%3d: Hash: %3d %s\n", j, table->hashcode(table->elements[j],table->max),table->toString(table->elements[j]));
            int n = AccessNb(table, table->elements[j]);
            if(n>0) sn+=n;
        }
    }
    printf("\nNumber of elements in the table: %d", table->length);
    printf("\nOccupation percentage in the table: %.2f", table->length/(double)table->max);
    printf("\nAverage number of access in the table: %.2f", sn/(double)table->max);
}

int AccessNb(TableHC* table, Object* object){
    int access=0;
    int h = table->hashcode(object, table->max);
    if(table->elements[h]==NULL){
        access=-1;
    }else{
        int re=h;
        int i=1;
        access++;
        initRand(table->max);
        while(table->toCompare(object, table->elements[re])!=0){
            access++;
            re=table->resolution(h,table->max, i++);
            if(table->elements[re]==NULL) return -1;
        }
    }
    return access;
}

double AvgAccessNb(TableHC* table){
    int sn=0;
    for(int i=0; i< table->max; i++){
        if(table->elements[i]!=NULL){
            int n=AccessNb(table, table->elements[i]);
            if(n>0) sn+=n;
        }
    }
    return sn/(double) table->length;
}

void listEntries(TableHC* table, int entry){
    printf("\nInputs to explore for the hashcode %3d\n", entry);
    if(table->elements[entry]==NULL){
        printf("Any object with the hashcode %d\n", entry);
    }else{
        int i=1;
        int re=entry;
        while(table->elements[re]!=NULL){
            printf("%3d %3d, hc: %3d %s", i, re, table->hashcode(table->elements[re], table->max), table->toString(table->elements[re]));
            re=table->resolution(re, table->max, i++);
        }
    }
}

void orderResolution(TableHC* table, int entry){
    printf("\nOrder of resolution for %d: \n", entry);
    initRand(table->max);
    for(int i=0;i<table->max;i++){
        printf("%2d", table->resolution(entry, table->max, i));
    }
    printf("\n");
}
