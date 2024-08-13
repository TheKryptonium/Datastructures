#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype>

#include "matrix.h"
#include "../4.List/list.h"


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

void writeGraph(Matrix* matrix){
    int max = matrix->max;

    for(int i=0; i<matrix->length; i++) printf("%s", matrix->sommits[i]);
    printf("\n");

    for(int i=0; i<matrix->length; i++){
        printf("\n%s :", matrix->sommits[i]);
        for(int j=0; j<matrix->length; j++){
            if(matrix->element[i*max+j]==True){
                printf("%s ", matrix->sommits[j]);
                if(matrix->value){
                    printf(":(%3d) ", matrix->value[i*max+j]);
                }
            }
        }
        printf(";");
    }
}

static void depth(Matrix* matrix, int number, int level){
    int max = matrix->max;
    matrix->mark[number]=True;
    for(int i=0; i<max; i++) printf("%5s", " ");
    printf("%s", matrix->sommit[number]);

    for(int i=0; i<max; i++){
        if(!matrix->mark[i] && matrix->element[max*number+i]==True){
            depthMatrix(matrix, i, level+1);
        }
    }
}

void DepthMatrix(Matrix* matrix){
    resetMark(matrix);
    for(int i=0; i<matrix->max; i++){
        if(!matrix->mark[i])DepthMatrix(matrix, i, 1);
    }
}

static void addQueue(Matrix* matrix, List* queue, int number){
    matrix->mark[number]=True;
    Successor* success = (Successor*)malloc(sizeof(Successor));
    success->number = number;
    insertLast(queue, success);
    
}

void widthMatrix(Matrix* matrix){
    int max = matrix->max;

    resetMark(matrix);
    List* queue = createList();

    for(int i=0; i<max; i++){
        if(!matrix->mark[i]){
            printf("\n %s", matrix->sommits[i]);
            addQueue(matrix, queue, i);

            while(!EOList(queue)){
                Successor* success = (Successor*)extract_head(queue);
                int s = success->number;

                for(int j=0; j<matrix->length; j++){
                    if(matrix->element[s*max+j]==True && !matrix->mark[j]){
                        printf("%s ", matrix->sommits[j]);
                        addQueue(matrix, queue, j);
                    }
                }
            }
        }

    }
}

static void writeStep(matrix* a, matrix* p, int k, int length, int max){
    if(k==-1){
        printf("Initial matrices of cost and last visited sommit.");
    }else{
        printf("Passage through the summit %d\n", k);
    }

    for(int i=0; i<length; i++){
        for(int j=0; j<length; j++){
            if(a[i*max+j]==INFINITY){
                printf(" %3s ","*");
            }else{
                printf("%d", a[i*max+j]);
            }
        }

        printf("%6s", " ");

        for(int j=0; j<length; j++){
            printf("%d", p[i*max+j]);
        }
        printf("\n");
    }
    
    printf("\n");
}


static void shortestPath(Matrix* graph, matrix* a, matrix* p){
    int max = graph->max;

    printf("Shortest path algorithm\n");
    for(int i=0; i<graph->length; i++){
        printf("In order to go from %s to :", graph->sommits[i]);
        for(int j=0; j<graph->length; j++){
            if(i!=j && a[i*max+j]!=INFINTY){
                printf("%s (cout = %d)", graph->sommits[j], a[i*max+j]);
                int k = p[i*max+j];
                printf("%s, %s", graph->sommits[i], graph->sommits[k]);
                while(k!=i){
                    k = p[i*max+k];
                    printf(", %s", graph->sommmits[k]);
                }
                printf("\n");
            }
        }
        printf("\n");
    }
    printf("\n");
}

static void initFloyd(Matrix* graph, matrix* a, matrix* p, int* ns){
    int max = graph->max;

    matrix ta = (int*)malloc(sizeof(int)*max*max);
    matrix tp = (int*)malloc(sizeof(int)*max*max);

    *ns =graph->length;
    for(int i=0; i<(*ns);i++){
        for(int j=0; j<(*ns); j++){
            ta[i*max+j]=graph->value[i*max+j];
            tp[i*max+j]=i;
        }
    }

    *a = ta;
    *p =tp;
}


void floyd(Matrix* graph){
    matrix a, p;
    int ns;
    int max = graph->max;

    initFloyd(graph, &a, &p, &ns);
    writeStep(&a, &p, -1, ns, graph->max);

    for(int k=0; k<ns; k++){
        for(int i=0; i<ns; i++){
            for(int j=0; j<ns; j++){
                if(a[i*max+k]!=INFINITY && a[k*max+j]!=INFINITY && a[i*max+k]+a[k*max+j]<a[i*max+j]){
                    a[i*max+j]=a[i*max+k]+a[k*max+j];
                    p[i*max+j]=p[k*max+j]
                }
            }
        }
        writeStep(&a,&p,k,ns,max);
    }
    shortestPath(graph, &a, &p);
    free(a); 
    free(p);
}