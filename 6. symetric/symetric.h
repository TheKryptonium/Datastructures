#ifndef SYMETRIC_H
#define SYMETRIC_H

typedef void Object;
typedef int boolean;
#define True 1
#define False 0


typedef struct element{
    Object* reference;
    struct element* next;
    struct element* previous;
}Element;

typedef struct{
    Element* top;
    Element* bottom;
    char* (*toString)(Object*);
    int (*toCompare)(Object*, Object*);
}Symetric;


void initSym(Symetric* sym, char* (*toString)(Object*), int (*toCompare)(Object*, Object*));
Symetric* createSym(char* (*toString)(Object*), int (*toCompare)(Object*, Object*));
Symetric* createSym();
boolean is_empty(Symetric* sym);

void push_bottom(Symetric* sym, Object* object);

Element* top(Symetric* sym);
Element* bottom(Symetric* sym);
Element* next(Element* elt);
Element* previous(Element* elt);

void exploreSymetric(Symetric* sym, void (*f)(Object*));
void exploreSymetricReverse(Symetric* sym, void (*f)(Object*));

Object* searchObject(Symetric* sym, Object* object);
void pop(Symetric* sym, Object* object);

#endif