#ifndef FNCH_H
#define FCNH_H

typedef int boolean;
#define True 1
#define False 0

typedef void Object;

int hash1(Object* key, int length);
int hash2(Object* key, int length);
int hash3(Object* key, int length);
int hash4(Object* key, int length);

int resolution1(int h, int length, int i);
int resolution2(int h,int k, int length, int i);
int resolution3(int h, int length, int i);
int resolution4(int h, int length, int i);

void initRand(int length);

#endif