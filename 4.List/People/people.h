#ifndef PEOPLE_H
#define PEOPLE_H

typedef char ch15 [16];

typedef struct{
    ch15 name;
    ch15 surname;
}People;

People* createPeople(ch15 name, ch15 surname);
People* createPeople();
void writePeople(void* object);
char* toStringPeople(void* object);
int comparePeople(void* objet1, void* objet2);

#endif