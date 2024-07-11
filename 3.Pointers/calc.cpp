#include <stdio.h>
#include "calc.h"

int sum(int v1, int v2){
    return v1+v2;
}

int dif(int v1, int v2){
    return v1-v2;
}

int mul(int v1, int v2){
    return v1*v2;
}

int div(int v1, int v2){
    return v1/v2;
}

int mod(int v1, int v2){
    return v1%v2;
}

int calc(int (*f), int v1, int v2){
    return f(v1,v2);
}