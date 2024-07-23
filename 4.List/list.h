#ifndef LIST_H
#define LIST_H

#define UNORDERED 0
#define GROWING 1
#define DECREASING 2

typedef void Object;

typedef int boolean;
#define True 1
#define False 0

typedef struct element{
    Object* reference;
    struct element* next;
}Element;

typedef struct{
    Element* head;
    Element* last;
    Element* current;
    unsigned int nb;
    unsigned int type;
    char* (*toString)(Object*);
    int (*compare)(Object*, Object*);

}List;

void  initList(List* li, unsigned int type, char* (*toString)(Object*), int (*compare)(Object*, Object*));
void  initList(List* li);

List* createList(unsigned int type, char* (*toString)(Object*), int (*compare)(Object*, Object*));
List* createList(unsigned int type);
List* createList();

boolean is_empty(List* li);
int nb(List* li);

void insertHead(List* li, Object* object);
void insertLast(List* li, Object* object);

void openList(List* li);
boolean EOList(List* li);
Object* current_object(List* li);

void list(List* li);
void list(List* li, void (*f)(Object*));

Object* search_object(List* li, Object* object);

Object* extract_head(List* li);
Object* extract_bottom(List* li);
boolean extract(List* li, Object* object);

void destroy_list(List* li);

void copy_list(List* li1, List* li2);

void insert_inOrder(List* li,Object* object);

#endif
