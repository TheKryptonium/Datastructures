#include <stdio.h>
#include <string.h>
#include "..\list.h"

typedef char ch3 [3];
char* msg(int n);

typedef List FactList;
typedef List RuleList;

void addFact(FactList* facts, int n);
void listFact(FactList* facts);
FactList* createFactList();


typedef struct{
    ch3 name;
    boolean mark;
    FactList* hypothesis;
    FactList* conclusions;
}Rule;

Rule* createRule(ch3 name){
    Rule* rule = new Rule();
    strcpy(rule->name, name);
    rule->hypothesis=createFactList();
    rule->conclusions=createFactList();
    rule->mark=False;
    return rule;
}

void addHypothesis(Rule* rule, int n){
    addFact(rule->hypothesis,n);
}

void addConclusions(Rule* rule, int n){
    addFact(rule->conclusions, n);
}

void listRule(Rule* rule){
    printf("Rule name: %s\n", rule->name);
    printf("    Hypothesis:\n");
    listFact(rule->hypothesis);
    printf(" Conclusions:\n");
    listFact(rule->conclusions);
}

void listAllRules(RuleList* rl){
    openList(rl);
    while(!EOList(rl)){
        Rule* index = (Rule*)current_object(rl);
        printf("%s", index->name);
        listRule(index);
    }
    print("\n");
}

typedef struct{
    int number;
}Fact;

Fact* createFact(int n){
    Fact* fact = new Fact();
    fact->number=n;
    return fact;
}

FactList* createFactList(){
    return createList();
}

void addFact(FactList* lf, int n){
    Fact* fact = createFact(n);
    insertLast(lf, fact);
}

void listFact(FactList* facts){
    openList(facts);
    while(!EOList(facts)){
        Fact* fact = (Fact*)current_object(facts);
        printf("    %s\n",fact->number);
    }
}

Fact* createFact(int n){
    return (Fact*)n;
}