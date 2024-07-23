#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "people.h"

People* createPeople(char* name, char* surname){
    People* people = new People();
    strcpy(people->name, name);
    strcpy(people->surname,surname);
    return people;
}

People* createPeople(){
    People* people = (People*)malloc(sizeof(People));
    ch15 name, surname;
    printf("Hello...\n");
    printf("Enter your name: ");
    scanf("%s",&name);
    printf("Enter your surname: ");
    scanf("%s",&surname);
    strcpy(people->name, name);
    strcpy(people->surname,surname);
    return people;
}

void writePeople(People* p){
    printf("%s %s\n", p->name, p->surname);
}

char* toStringPeople(People* p){
    char* msg = (char*)malloc(30);
    sprintf(msg, "%s %s",p->name, p->surname);
    return msg;
}

int comparePeople(People* p1, People* p2){
    return strcmp(toStringPeople(p1), toStringPeople(p2));
}

void writePeople(Object* p){
    writePeople((People*)p);
}

char* toStringPeople(Object* p){
    return toStringPeople((People*)p);
}

int comparePeople(Object* p1, Object* p2){
    return comparePeople((People*)p1, (People*)p2);
}


