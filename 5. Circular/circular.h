#ifndef CIRCULAR_H
#define CIRCULAR_H

typedef void Object;

typedef struct element{
    Object* reference;
    element* next;
}Element;

typedef struct{
    Element* last;
}Circular;

void initCircular(Circular* circus);
Circular* createCircular();


void push_top(Circular* circus, Object* object);
void push_bottom(Circular* circus, Object* object);

Element* top(Circular* circus);
Element* bottom(Circular* circus);
Element* next(Element* elt);
void exploreCircular(Element* start, void (*f)(Object*));


#endif