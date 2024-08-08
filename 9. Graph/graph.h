#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include "..\4.List\list.h"
#include "..\8. Tables\table.h"

#define INFINITE INT_MAX

typedef struct{
    Object* object;
    boolean mark;
    int num;
    List succesors;
}Sommit;

typedef struct {
    Sommit* somsuccess;
    int cout;
}Successor;

typedef struct{
    Table* table;
    boolean value;
}Graph;

Graph* createGraph(int max, boolean value, char* (*toString)(Object*), int (*toCompare)(Object*, Object*));
Graph* createGraph(int max, boolean value);
void destroyGraph(Graph* graph);
void addSommit(Graph* graph, Object* object);
void addArch(Graph* graph, Object* start, Object* end, int cout);

Graph* readGraph(FILE* fe, int max);

void writeGraph(Graph* graph);
void DepthExplore(Graph* graph);
void WidthExplore(Graph* graph);
void lessLength(Graph* graph, int initial);

char* toStringSommit(Object* object);
int compareSommit(Object* object1, Object* object2);

#endif