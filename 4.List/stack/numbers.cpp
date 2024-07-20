#include <stdio.h>
#include <stdlib.h>
#include "numbers.h"

Integer* createInteger(int value){
    Integer* i = new Integer();
    i->value=value;
    return i;
}

Integer* integer(int value){
    return createInteger(value);
}

char* toStringInteger(void* object){
    char* number = (char*) malloc(50);
    sprintf(number, "%d", ((Integer*)object)->value);
    return number;
}

void writeInteger(void* Object){
    Integer* i = new Integer();
    printf("%d\n", i->value);
}

int compareIntegers(void* objet1, void* objet2){
    if(((Integer*)objet1)->value==((Integer*)objet2)->value){
        return 0;
    }else{
        return (((Integer*)objet1)->value > ((Integer*)objet2)->value) ? 1:-1;
    }
}

int compareIntegersCar(void* objet1, void* objet2){
    if(atoi((char*)objet1)==atoi((char*)objet2)){
        return 0;
    }else{
        return (atoi((char*)objet1)>atoi((char*)objet2))? 1:-1;
    }
}

Real* createReal(double value){
    Real* real = new Real();
    real->value=value;
    return real;
}

void writeReal(void* object){
    Real* real = (Real*) object;
    printf("%.2f\n", real->value);
}