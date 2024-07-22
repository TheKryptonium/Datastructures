#include <stdio.h>
#include <stdlib.h>
#include "circular.h"

void initCircular(Circular* circus){
    circus->last=NULL;
}

Circular* createCircular(){
    Circular* circus = new Circular();
    initCircular(circus);
    return circus;
}

static Element* createElement(){
    return new Element();
}

void push_top(Circular* circus, Object* object){
    Element* elt = createElement();
    elt->reference=object;
    if(circus->last==NULL){
        elt->next=elt;
        circus->last=elt;
    }else{
        elt->next=circus->last->next;
        circus->last->next=elt;
    }
}

void push_bottom(Circular* circus, Object* object){
    Element* elt = createElement();
    elt->reference=object;
    if(circus->last==NULL){
        elt->next=next;
        circus->last= elt;
    }else{
        elt->next=circus->last->next;
        circus->last->next=elt;
        circus->last=elt;
    }
    
}

Element* top(Circular* circus){
    return circus->last->next;
}

Element* bottom(Circular* circus){
    return circus->last;
}

Element* next(Element* elt){
    return (elt==NULL)?NULL:elt->next;
}

void exploreCircular(Element* start, void (*f)(Object*)){
    if(start==NULL){
        printf("Empty list");
    }else{
        f(start->reference);
        Element* elt=createElement();
        elt=start->next;
        while(elt!=start){
            f(elt->reference);
            elt->next;
        }
        printf("\n");
    }
}