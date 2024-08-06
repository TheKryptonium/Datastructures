#ifndef TABLEHCC_H
#define TABLEHCC_H

#include "fnch.h"

#define NILE -1

typedef struct{
    Object* object; 
    int next;
}tableElement;

typedef struct{
    int max;
    int length;
    Object** elements;
    char* (*toString)(Object*);
    int (*toCompare)(Object*,Object*);
    int (*hashcode)(Object*,int);
    int (*resolution)(int, int, int);
}TableHCC;


TableHCC* createTableHCC(int max, char* (*toString)(Object*), int (*toCompare)(Object*,Object*), int (*hashcode)(Object*, int), int (*resolution)(int, int, int));
TableHCC* createTableHCC(int max);
void appendHCC(TableHCC* table, Object* object);
Object* lookFor(TableHCC* table, Object* object);
void listHCC(TableHCC* table);
int AccessNb(TableHCC* table, Object* object);
int AvgAccessNb(TableHCC* table);
void listEntry(TableHCC* table, int entry);
void orderResolution(TableHCC* table,int entry);

#endif