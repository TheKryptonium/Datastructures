#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

char* toStringSommit(Object* object){
    return (char*)object;
}

int toCompareSommit(Object* object1, Object* object2){
    return strcmp(toStringSommit(object1), toStringSommit(object2));
}

Sommit* getSommit(Graph* graph, int index){
    return (Sommit*)graph->table->elements[index];
}

void markSommit(Graph* graph, int n){
    getSommit(graph, n)->mark=True;
}

boolean isMarked(Graph* graph, int n){
    return getSommit(graph, n)->mark;
}

char* SommitName(Graph* graph, Sommit* sommit){
    return graph->table->toString(sommit);
}

char* SommitName(Graph* graph, int n){
    return SommitName(graph, getSommit(graph,n));
}

int Length(Graph* graph){
    return Length(graph->table);
}

static void resetMark(Graph* graph){
    for(int j=0; j<Length(graph); j++) getSommit(graph,j)->mark=False;
}

Graph* createGraph(int max, boolean value, char* (*toString)(Object*), int (*toCompare)(Object*,Object*)){
    Graph* graph= new Graph();
    graph->table=createTable(max, toString, toCompare);
    graph->value=value;
    return graph;
}

Graph* createGraph(int max, boolean value){
    return createGraph(max, value, toStringSommit, toCompareSommit);
}

void destroyGraph(Graph* graph){
    for(int j=0; j<Length(graph);j++){
        destroy_list(&(getSommit(graph,j)->succesors));
    }
    destroyTable(graph->table);
}

static Sommit* createSommit(){
    return new Sommit();
}

void addSommit(Graph* graph, Object* object){
    Sommit* sommit= createSommit();
    sommit->object=object;
    sommit->mark=False;
    sommit->num=Length(graph->table);
    initList(&sommit->succesors);
    insertTable(graph->table,sommit);
}

void addArch(Graph* graph, Object* start, Object* end, int cout){
    Sommit st;
    st.object=start;
    Sommit* sommit= (Sommit*) sequentialAccess(graph->table,&st);
    if(sommit==NULL){
        printf("The sommit %s doesn't exist", SommitName(graph,&st));
        return;
    }

    Sommit ed;
    ed.object=end;
    Sommit* sommit=(Sommit*) sequentialAccess(graph->table,&ed);

    if(sommit==NULL){
        printf("The sommit %s doesn't exist", SommitName(graph, &ed));
        return;
    }

    Successor* success= new Successor();
    success->somsuccess=&ed;
    success->cout=cout;
    insertLast(&sommit->succesors,success);
}

void writeGraph(Graph* graph){
    printf("Let's explore this %s graph...\n\n", graph->value?"valued":"non valued");
    for(int j=0;j<Length(graph);j++){
        Sommit* sommit= getSommit(graph, j);
        List* successors = &sommit->succesors;
        printf("%s: ", graph->table->toString(sommit));
        openList(successors);
        while(!EOList(successors)){
            Successor* success=(Successor*)current_object(successors);
            printf("%s",SommitName(graph,success->somsuccess));
            if(graph->value)printf("(%3d), ",success->cout);
        }
        printf(";\n");
    }

}

static void Depth(Graph* graph, Sommit* sommit, int level){
    sommit->mark=True;
    for(int j=0; j<level;j++)printf("%5s"," ");
    printf("%s", SommitName(graph,sommit));

    List* successors = &sommit->succesors;
    openList(successors);
    while(!EOList(successors)){
        Successor* success=(Successor*)current_object(successors);
        if(!success->somsuccess->mark) Depth(graph, success->somsuccess, level+1);
    }
}

void DepthExplore(Graph* graph){
    resetMark(graph);
    for(int j=0; j<Length(graph);j++){
        Sommit* sommit=getSommit(graph, j);
        if(!sommit->mark) Depth(graph, sommit,1);
    }
}

static void insertQueue(List* queue, Sommit* sommit){
    sommit->mark=True;
    Successor* success= new Successor();
    success->somsuccess=sommit;
    insertLast(queue,success);
}

void WidthExplore(Graph* graph){
    printf("Width Exploration...\n");
    resetMark(graph);
    List* queue= createList();

    for(int j=0; j<Length(graph);j++){
        Sommit* start = getSommit(graph,j);
        if(!start->mark){
            printf("\n %s", SommitName(graph, start));
            insertQueue(queue, start);

            while(!EOList(queue)){
                Successor* success= (Successor*)extract_bottom(queue);
                start=success->somsuccess;

                List* successors = &start->succesors;
                openList(successors);
                while(!EOList(successors)){
                    Successor* success = (Successor*)current_object(successors);
                    Sommit* sommit=success->somsuccess;
                    if(!sommit->mark){
                        printf("%s ", SommitName(graph, sommit));
                        insertQueue(queue, sommit);
                    }
                }
            }
        }
    }

}

static boolean allMarked(Graph* graph){
    int index=0;
    while(isMarked(graph,index) && index<Length(graph)) index++;
    return (index>=Length(graph));
}

static int dMin(Graph* graph, int* d){
    int min = INFINITE;
    int nmin=0;
    for(int i=0; i<Length(graph);i++){
        if(isMarked(graph,i)){
            if(d[i]<=min){min=d[i]; nmin=i;}
        }
    }
    return nmin;
}

void writeResults(Graph* graph, int initial, int* d, int* pr){
    printf("\nThe less length path (from the end): \n");
    printf("In order to go from %s to: \n", SommitName(graph, initial));
    for(int j=0; j<Length(graph);j++){
        if((j!=initial) && (d[j]!=INFINITE)){
            printf(" %s (cout=%d): %s, ", SommitName(graph,j),d[j], SommitName(graph,j));
            int i=j;
            while(i!=initial){
                printf("%s ",SommitName(graph,pr[i]));
                i=pr[i];
            }
            printf(", %s\n", SommitName(graph, pr[i]));
        }
    }
    printf("\n");
}   

void lessLength(Graph* graph, int initial){
    int* d= (int*)malloc(sizeof(int)*Length(graph));
    int* pr=(int*)malloc(sizeof(int)*Length(graph));

    resetMark(graph);
    for(int i=i=0;i<Length(graph);i++){
        d[i]=INFINITE;
        pr[i]=initial;
    }
    d[initial]=0;

    List* successors = &(getSommit(graph,initial)->succesors);
    openList(successors);
    while(!EOList(successors)){
        Successor* success=(Successor*)current_object(successors);
        int i = success->somsuccess->num;
        d[i]= success->cout;
    }

    printf("Initial: %d", initial);
    markSommit(graph,initial);

    while(!allMarked(graph)){
        int m =dMin(graph,d);
        markSommit(graph,m);

        if(d[m]!=INFINITE){
            successors = &(getSommit(graph,m)->succesors);
            openList(successors);
            while(!EOList(successors)){
                Successor* success= (Successor*)current_object(successors);
                int k =success->somsuccess->num;
                if(!isMarked(graph,k)){
                    int v = d[m]+success->cout;
                    if(v<d[k]){
                        d[k]=v;
                        pr[k]=m;
                    }
                }
            }
        }
    }
    writeResults(graph, initial,d,pr);

}