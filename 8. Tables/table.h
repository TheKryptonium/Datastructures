#ifndef TABLE_H
#define TABLE_H

typedef void Object;

typedef int boolean;
#define True 1
#define False 0

typedef struct{
    int max;
    int length;
    Object** elements;
    char* (*toString)(Object*);
    int (*toCompare)(Object*, Object*);
}Table;

Table* createTable(int max, char* (*toString)(Object*), int (*toCompare)(Object*, Object*));
Table* createTable(int max);
void destroyTable(Table* table);
boolean insertTable(Table* table, Object* object);

int Length(Table* table);

Object* locateElement(Table* table, int n);
Object* sequentialAccess(Table* table, Object* object);
Object* dichotomy(Table* table, Object* object, int left, int right);
Object* dichotomy(Table* table, Object* object);

void sort(Table* table);
void listTable(Table* table);

#endif