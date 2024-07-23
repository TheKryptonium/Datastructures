#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symetric.h"

static char* toString(Object* object){
    return (char*)object;
}

static int toCompare(Object* objet1, Object* objet2){
    return strcmp(toString(objet1), toString(objet2));
}

void initSym(Symetric* sym, char* (*toString)(Object*), int (*toCompare)(Object*, Object*)){
    sym->top=NULL;
    sym->bottom=NULL;
    sym->toString=toString;
    sym->toCompare=toCompare;
}

Symetric* createSym(char* (*toString)(Object*), int (*toCompare)(Object*, Object*)){
    Symetric* sym = new Symetric();
    initSym(sym, toString, toCompare);
    return sym;
}

Symetric* createSym(){
    return createSym(toString, toCompare);
}

boolean is_empty(Symetric* sym){
    return(sym->top==NULL);
}

static Element* createElement(){
    return new Element();
}

void push_bottom(Symetric* sym, Object* object){
    Element* elt = createElement();
    elt->reference = object;
    elt->next=NULL;
    if(is_empty(sym)){
        elt->previous = NULL;
        sym->top=elt;
    }else{
        elt->previous = sym->bottom;
        sym->bottom->next = elt;        
    }
    sym->bottom=elt;
}

Element* top(Symetric* sym){
    return sym->top;
}

Element* bottom(Symetric* sym){
    return sym->bottom;
}

Element* next(Element* elt){
    return elt->next;
}

Element* previous(Element* elt){
    return elt->previous;
}

void exploreSymetric(Symetric* sym, void (*f)(Object*)){
    if(is_empty(sym)){
        printf("The symetric list is empty");
    }else{
        Element* index= top(sym);
        while(index!=NULL){
            f(index->reference);
            index=next(index);
        }
    }
}

void exploreSymetricReverse(Symetric* sym, void (*f)(Object*)){
    if(is_empty(sym)){
        printf("The symetric list is empty");
    }else{
        Element* index= bottom(sym);
        while(index!=NULL){
            f(index->reference);
            index=previous(index);
        }
    }
}

static Element* searchElement(Symetric* sym, Object* object){
    boolean found = False;
    Element* cursor = top(sym);
    while(!found && cursor!=NULL){
        found = sym->toCompare(cursor->reference, object)==0;
        if(!found) cursor = next(cursor);
    }
    return found? cursor:NULL;

}

Object* searchObject(Symetric* sym, Object* object){
    Element* index = searchElement(sym, object);
    return(index==NULL)? NULL:index->reference;
}

static void popSym(Symetric* sym, Element* extract){
    if(sym->top==extract && sym->bottom==extract){
        sym->top=NULL;
        sym->bottom=NULL;
    }else if(sym->top==extract){
        sym->top->next->previous=NULL;
        sym->top=top(sym)->next;
    }else if(sym->bottom==extract){
        sym->bottom->previous->next=NULL;
        sym->bottom=sym->bottom->previous;
    }else{
        extract->next->previous=extract->previous;
        extract->previous->next=extract->next;
    }
}

void pop(Symetric* sym, Object* object){
    Element* elt = searchElement(sym,object);
    if(elt!=NULL) popSym(sym, elt);
}