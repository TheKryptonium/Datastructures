#ifndef NUMBERS_H
#define NUMBERS_H

typedef struct{
    int value;
}Integer;

Integer* createInteger(int value);
Integer* integer(int value);
void writeInteger(void* object);
char* toStringInteger(void* object);
int compareIntegers(void* objet1, void* objet2);
int compareIntegersCar(void* objet1, void* objet2);


typedef struct{
    double value;
}Real;

Real* createReal(double value);
Real* real(double value);
void writeReal(void* object);


#endif