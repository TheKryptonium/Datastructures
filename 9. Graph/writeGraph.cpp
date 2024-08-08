#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef MATRIX
#include "graph.h"
#else
#include"matrix.h"
typedef Matricial Graph
#endif

typedef char NameSommit[20];
int c;

void readWhite(FILE* fe){
    while(((c==' ' || c=='\n' || c==13)) && !feof(fe)){
        c=getc(fe);
    }
}

void readWord(FILE* fe, char* string){
    char* string;
    readWhite(fe);
    while(isalpha(c) || isdigit(c)){
        *string++=(char)c;
        c=getc(fe);
    }
    *string=0;
    readWhite(fe);
}

Graph* readGraph(FILE* fe, int max){
    boolean value=False;
    #ifdef MATRIX
    Graph* graph=createGraphMat(max,False);
    #else
    Graph* graph=createGraph(max, False);
    #endif

    c=getc(fe);
    while(c!=';'){
        char* start = (char*)malloc(20);
        readWord(fe,start);
        addSommit(graph,start); 
    }

    while(c!=EOF){
        c=getc(fe);
        NameSommit start;

        readWord(fe,start);
        if(c!=':'){
            if(c!= EOF) printf("%c (%d)", c,c);
            graph->value=value;
            return graph;
        }

        c=getc(fe);
        while (c!=';'){
            NameSommit end;
            readWord(fe,end);
            int cout;
            if(c=='('){
                value=True;
                fscanf(fe,"%d", &cout);
                c=getc(fe);
                if(c!=')') printf("Manque)\n");
                c=getc(fe);
                readWhite(fe);
            }else{
                cout=0;
            }
            addArch(graph,start,end,cout);

        }      
    }
    graph->value=value;
    return graph;
}