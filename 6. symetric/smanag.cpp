#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include "symetric.h"
#include "people.h"

int menu(){
    printf("    **********************************SYMETRIC LIST MANAGEMENT**********************************    \n");
    printf("\n");
    printf("0. Quit\n");
    printf("1. Symetric List Initialisation\n");
    printf("2. Push an element at the bottom ?\n");
    printf("3. Explore the list\n");
    printf("4. Reverse exploration of the list\n");
    printf("5. Pop an element\n");
    printf("\n");
    
    int code;
    printf("Let's make a choice: ");
    scanf("%d", &code); getchar();
    printf("\n");

    return code;
}

int main(){
    Symetric* sym = createSym();
    boolean end = False;

    while(!end){
        switch (menu())
        {
        case 0:
            end = True;
        break;

        case 1:
            initSym(sym, toStringPeople, comparePeople);
        break;

        case 2:{
            People* people = createPeople();
            push_bottom(sym, people);
        }break;

        case 3:{
            exploreSymetric(sym, writePeople);
        }break;

        case 4:
            exploreSymetricReverse(sym, writePeople);
        break;

        case 5:{
            printf("Which element do you want to pop from this list ?");
            ch15 name; scanf("%s", &name);
            ch15 surname; scanf("%s", &surname);
            People* found = createPeople(name, surname);
            People* cursor = (People*)searchObject(sym, found);
            if(cursor==NULL){
                printf("%s is unknown", name);
            }else{
                writePeople(cursor);
                pop(sym, cursor);
            }
        }break;
        
        default:
            printf("Choose a correct number or quit!");
        break;
        }
    }
    return 0;
}