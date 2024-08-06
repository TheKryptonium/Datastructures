#ifndef TABLEHC_H
#define TABLEHC_H

#include "fnch.h"

typedef struct{
    int max;
    int length;
    Object** elements;
    char* (*toString)(Object*);
    int (*toCompare)(Object*, Object*);
    int (*hashcode)(Object*, int);
    int (*resolution)(int, int, int);
}TableHC;

TableHC* createTableHC(int max, char* (*toString)(Object*), int (*toCompare)(Object*, Object*), int (*hashcode)(Object*, int), int (*resolution)(int, int, int));
TableHC* createTableHC(int max);
boolean appendHC(TableHC* table, Object* object);
Object* lookFor(TableHC* table, Object* object);
void listHC(TableHC* table);
int AccessNb(TableHC* table, Object* object);
double AvgAccessNb(TableHC* table);
void listEntry(TableHC* table, int entry);
void orderResolution(TableHC* table, int entry);

#endif