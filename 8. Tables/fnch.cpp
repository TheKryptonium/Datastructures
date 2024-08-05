#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>
#include "fnch.h"
#include "..\1.Recursitivity\basics.h"


int hash1(char* key, int length){
    int sum=0;
    for(int i=0; i<strlen(key); i++){
        if(isalpha(key[i])) sum+=toupper(key[i])-'A'+1;
    }
    return sum%length;
}

int hash2(char* key, int length){
    int sum=0;
    for(int i=0; i<strlen(key);i++){
        if (isalpha(key[i])) sum+=toupper(key[i]);
    }
    return sum%length;
}

int hash3(long key, int length){
    return key%length;
}

int hash4(long key, int length){
    return convert_base10(key,11)%length;
}

int hash1(Object* object, int length){
    return hash1((char*)object, length);
}

int hash2(Object* object, int length){
    return hash2((char*)object, length);
}

int hash3(Object* object, int length){
    return hash3(*(long*)object,length);
}

int hash4(Object* object, int length){
    return hash4(*(long*)object,length);
}


int resolution(int h, int length, int i){//r(i)=i
    return (h+i)%length;
}

int resolution2(int h,int k,int length, int i){//r(i)=k*i
    return (h+k*i)%length;
}

int resolution3(int h, int length, int i){//quadratic resolution r(i)=i*i
    return (h+i*i)%length;
}

int rand(int length, boolean reInit){
    static int r=1;
    static int n4=length*4;
    if(reInit){
        n4=length*4;
        r=1;
        return r;
    }else{
        r*=4;
        r%=n4;
        return r/4;
    }
}

void initRand(int length){
    rand(length,True);
}

int resolution4(int h, int length, int i){
    return(h+rand(length,False)%length);
}