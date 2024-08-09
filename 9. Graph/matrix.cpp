#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype>

#include "matrix.h"

static void resetMark(Matrix* matrix){
    for(int j=0; j<matrix->length; j++) matrix->mark[j]=False;
}

Matrix* createMatrix(int max, boolean value){
    Matrix* matrice = (Matrix*)malloc(sizeof(Matrix));
    matrice->length=0;
    matrice->max=max;
    matrice->value=value;
    matrice->sommits=(NameSommit*)malloc(sizeof(NameSommit)*max);
    matrice->element=(int*)malloc(sizeof(int)*max*max);
    matrice->value=(int*)malloc(sizeof(int)*max*max);
    matrice->mark=(boolean*)malloc(sizeof(boolean)*max*max);

    for(int i=0; i<max; i++){
        for(int j=0; j<max;j++){
            matrice->element[i*max+j]=False;
            matrice->value[i*max+j]=INFINTY;
        }
    }

    for(int i=0;i<max;i++) matrice[i*max+i]=0;
    resetMark(matrice);

    return matrice;
}


void destroyMatrix(Matrix* matrice){
    free(matrice->nameSommit);
    free(matrice->mark);
    free(matrice->element);
    free(matrice->value);
    free(matrice);
}

static int range(Matrix* matrice, NameSommit sommit){
    int i=0;
    boolean found = False;

    while(i<matrice->max && !found){
        found = strcmp(matrice->sommits[i], sommit)==0;
        if(!found) i++;
    }

    return found ? i:-1;
}

void addSommit(Matrix* matrice, NameSommit NameSommit){
    if(range(matrice, sommit)==-1){
        if(matrice->length<matrice->max){
            strcpy(matrice->sommits[matrice->length++], NameSommit);
        }else{
            printf("\nnUmber of sommits: %d", matrice->max);
        }
    }else{
        printf("%s already defined", NameSommit);
    }
}

void addArch(Matrix* matrice, NameSommit start, NameSommit end, int cout){
    int max = matrice->max;
    int right = range(matrice, start);
    int left= range(matrice, end);
    matrice->element [right*max+left]=True;
    matrice->value [right*max+left] = cout;
}