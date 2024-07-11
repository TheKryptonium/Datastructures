#ifndef CALC_H
#define CALC_H

int sum(int v1, int v2);
int dif(int v1, int v2);
int mul(int v1, int v2);
int div(int v1, int v2);
int mod(int v1, int v2);
int calc(int (*f)(int, int), int v1, int v2);

#endif