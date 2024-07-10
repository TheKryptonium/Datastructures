#include <iostream>
#include "basics.h"

using namespace std;

unsigned int factorial(unsigned int number){
    if(number==0)
        return 1;
    
    return number*factorial(number-1);
}

unsigned int fibonnacci(unsigned int number){
    if (number<2)
        return 0;
    
    return fibonnacci(number-1)+fibonnacci(number-2);
}

void increasing_loop(int d, int f, int i){
    if(d<f){
        cout<<"Loop index: "<<d<<endl;
        increasing_loop(d+i,f,i);
    }
}

void decreasing_loop(int d, int f, int i){
    if(d<f){
        decreasing_loop(d+i,f,i);
        cout<<"Loop index: "<<d<<endl;
    }
}

int convert_base10(int number, int base){
    int q= number/10;
    int r = number%10;

    if(q==0)
        return r;

    return convert_base10(q,base)*base+r;
    
}

void convert_baseB(int number, int base){
    static char convert[]= "0123456789ABCDEF";
    long q = number/base;
    long r = number%base;
    if(q!=0) convert_baseB(q,base);
    cout<<convert[r];
}

void convert_baseAfromB(int number, int baseA, int baseB){
    convert_baseB(convert_base10(number,baseA), baseB);
}

double power(int number, int r){
    if(r==0){
        return 1;
    }else{
        if(r%2==0){
            return power(number,r/2)*power(number,r/2);
        }else{
            return number*power(number,r/2)*power(number,r/2);
        }
    }

}

void hanoi(int n, char D, char B, char I){
   if(n>0){
        hanoi(n-1, D, I, B);
        cout<<"Moving from "<<D<<"-->"<<B;
        hanoi(n-1, I, B, D);
   }
}