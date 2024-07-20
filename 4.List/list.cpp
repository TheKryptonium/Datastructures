#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

static int compare(void* el1, void* el2){
    return strcmp((char*)el1, (char*)el2);
}

static char* toString(void* el){
    return (char*)el;
}

static Element* createElement(){
    return (Element*)malloc(sizeof(Element));
}

static void insertAfter(List* li, void* objet, Element* el){
    if(el==NULL) insertHead(li, objet);
    
    Element* elt= createElement();
    elt->reference=objet;
    elt->next=el->next;
    el->next=elt;
    if(el==li->last) li->last;
    li->nb++;
}

static void* extract_after(List* li, Element* previous){
    if(previous==NULL){
        return extract_head(li);
    }else{
        Element* extract=previous->next;
        if(extract!=NULL){
            previous->next=extract->next;
            if(extract==li->last) li->last=previous;
            li->nb--;
        }
        return (extract!=NULL)?extract->reference:NULL;
    }
}

static boolean inOrder(void* objet1, void* objet2, boolean growing_order,int (*compare)(void*,void*)){
    boolean order = compare(objet1, objet2)<0;
    if(!growing_order) order = !(order);
    return order; 
}

void initListe(List* li, unsigned int type,
char* (*toString)(void* el),
int (*compare)(void* el1, void* el2)){
    li->head=NULL;
    li->last=NULL;
    li->current=NULL;
    li->nb=0;
    li->type=type;
    li->toString=toString;
    li->compare=compare;
}

void initListe(List* li){
    initListe(li, UNORDERED, toString, compare);
}

List* createList(unsigned int type, char* (*toString)(void* element), int (*compare)(void* el1, void* el2)){
    List* li=(List*)malloc(sizeof(List));
    initListe(li,type, toString, compare);
    return li;
}

List* createList(unsigned int type){
    return createList(type, toString, compare);
}

List* createList(){
    return createList(UNORDERED,toString, compare);
}

boolean is_empty(List* li){
    return(li->nb==0);
}

int nb(List* li){
    return li->nb;
}

void insertHead(List* li, void* object){
    Element* el = createElement();
    el->reference=object;
    el->next=li->head;
    li->head=el;
    if(li->last==NULL) li->last=el;
    li->nb++;
}

void insertLast(List* li, void* object){
    insertAfter(li, object, li->last);
}

void openList(List* li){
    li->current=li->head;
}

boolean EOList(List* li){
    return(li->current==NULL);
}

static Element* current_element(List* li){
    Element* ptc = li->current;
    if(li->current!=NULL){
        li->current=li->current->next;
    }
    return ptc;
}

void* current_object(List* li){
    return (current_element(li)==NULL)?NULL:current_element(li);
}

void list(List* li){
    openList(li); unsigned int index=1;
    while(!EOList(li)){
        printf("%d. %s", index, li->toString(current_object(li)));
        index++;
    }
}

void list(List* li, void (*f)(void*)){
    openList(li); int index=1;
    while(!EOList(li)){
        f(current_element(li));
    }
}

void* search_object(List* li, void* object){
    openList(li);
    boolean found = False;
    while(!EOList(li) && !found){
        found = li->compare(current_object(li),object)==0;
    }
    return found?object:NULL;
}

void* extract_head(List* li){
    Element* extract=li->head;
    if(!is_empty(li)){
        li->head=li->head->next;
        if(li->head==NULL) li->last==NULL;
        li->nb--;
    }
    return (extract!=NULL)?extract->reference:NULL;
}


void* extract_bottom(List* li){
    void* extract;
    if(is_empty(li)){
        extract==NULL;
    }else if(li->head==li->last){
        extract_head(li);
    }else{
        Element* index = li->head;
        while(index->next!=li->last)index=index->next;
        extract = extract_after(li, index);
    }
    return extract;
}

void* extract(List* li, void* object){   
    if(search_object(li, object)==NULL){
        return extract_head(li);
    }else{
        Element* index = li->head;
        while(index->next!=search_object(li, object)) index= index->next;
        return extract_after(li, index);
    }
}

void destroy_list(List* li){
    openList(li);
    while(!EOList(li)){
        Element* ptc = current_element(li);
        free(ptc->reference);
        free(ptc);
    }
    initListe(li);
}

void copy_list(List* li1, List* li2){
    destroy_list(li1);
    *li1=*li2;
    initListe(li2);
}

void insert_inOrder(List* li, void* object){
    if(is_empty(li)){
        insertHead(li, object);
        printf("Insertion at the top...\n");
    }else{
        Element* index = li->head;
        if(inOrder(object,index->reference, li->type==1, li->compare)){
            printf("Insertion at the top...\n");
            insertHead(li, object);
        }else{
            printf("Insertion int he middle or at the bottom of list");
            boolean found = False;
            Element* previous = NULL;

            while(index!=NULL && !found){
                previous = index;
                index = index->next;
                if(index!=NULL) found = inOrder(object, index->reference,li->type==1,li->compare);
            }
            insertAfter(li,object,previous);
        }        
    }
}

