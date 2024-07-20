#ifndef LIST_H
#define LIST_H

#define UNORDERED 0
#define GROWING 1
#define DECREASING 2

typedef int boolean;
#define True 1
#define False 0

typedef struct element{
    void* reference;
    struct element* next;
}Element;

typedef struct{
    Element* head;
    Element* last;
    Element* current;
    unsigned int nb;
    unsigned int type;
    char* (*toString)(void*);
    int (*compare)(void*, void*);

}List;

void  initList(List* li, unsigned int type, char* (*toString)(void*), int (*compare)(void*, void*));
void  initList();

List* createList(unsigned int type, char* (*toString)(void*), int (*compare)(void*, void*));
List* createList(unsigned int type);
List* createList();

boolean is_empty(List* li);
int nb(List* li);

void insertHead(List* li, void* object);
void insertLast(List* li, void* object);

void openList(List* li);
boolean EOList(List* li);
void* current_object(List* li);

void list(List* li);
void list(List* li, void (*f)(void*));

void* search_object(List* li, void* object);

void* extract_head(List* li);
void* extract_bottom(List* li);
void* extract(List* li, void* object);

void destroy_list(List* li);

void copy_list(List* li1, List* li2);

void insert_inOrder(List* li,void* object);

#endif
