#ifndef PEOPLE_H
#define PEOPLE_H

typedef char ch15 [16];
typedef void Object;

typedef struct{
    ch15 name;
    ch15 surname;
}People;

People* createPeople(char* name, char* surname);
People* createPeople();
void writePeople(Object* object);
char* toStringPeople(Object* object);
int comparePeople(Object* objet1, Object* objet2);

#endif