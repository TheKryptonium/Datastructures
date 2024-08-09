#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

typedef int boolean;
#define True 1
#define False 0
typedef char NameSommit[20];
#define INFINTY INT_MAX

typedef int* matrix;

typedef struct{
    int length;
    int max;
    boolean value;
    NameSommit* sommits;
    matrix element;
    matrix value;
    boolean* mark;
}Matrix;

Matrix* createMatrix(int max, boolean value);
void destroyMatrix(Matrix* matrix);
void addSommit(Matrix* matrix, NameSommit sommit);
void addArch(Matrix* matrix, NameSommit start, NameSommit end, int cout);
void readGraph(FILE* fe, int max);
void writeGraph(Matrix* matrix);
void DepthMatrix(Matrix* matrix);
void widthMatrix(Matrix* matrix);
void floyd(Matrix* matrix);
void productClosure(Matrix* matrix);
void marshall(Matrix* matrix);

#endif
