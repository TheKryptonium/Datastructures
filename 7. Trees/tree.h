#ifndef TREE_H
#define TREE_H


typedef void Object;

typedef int boolean;
#define True 1
#define False 0 

typedef struct node{
    Object* reference;
    struct node* right;
    struct node* left;
    int fact;
}Node;

typedef struct{
    Node* root;
    char* (*toString)(Object*);
    int (*toCompare)(Object*,Object*);
}Tree;

Node* getRoot(Tree* tree);
Node* getLeft(Node* node);
Node* getRight(Node* node);

Object* getObject(Node* node);
void setRoot(Tree* tree, Node* root);
void setString(Tree* tree, char* (*toString)(Object*));
void setCompare(Tree* tree, int (*toCompare)(Object*, Object*));


Node* cNd(Object* object, Node* left, Node* right);
Node* cNd(Object* object);
Node* cF(Object* object);

void initTree(Tree* tree, Node* root, char* (*toString)(Object*), int (*toCompare)(Object*, Object*));
Tree* createTree(Node* root, char* (*toString)(Object*), int (*toCompare)(Object*, Object*));
Tree* createTree(Node* root);
Tree* createTree();

void prefix(Tree* tree);
void infix(Tree* tree);
void postfix(Tree* tree);
void indentPrefix(Tree* tree);
void indentInfix(Tree* tree);
void indentPostfix(Tree* tree);

Node* searchNode(Tree* tree, Object* object);
void inWidth(Tree* tree);

int length(Node* node);
int length(Tree* tree);
boolean isLeaf(Node* node);
int leafLength(Tree* tree);
void listLeaf(Tree* tree);
int maxIdent(Tree* tree);
int lgIdent(Tree* tree);
int height(Tree* tree);
boolean degenerated(Tree* tree);

Tree* copyTree(Tree* tree);
Tree* copyTree(Tree* tree, Object* (*toClone)(Object*));
void destroyTree(Tree* tree);
void destroyTree(Tree* tree, Object* (*toDestroy)(Object*));

void drawTree(Tree* tree, FILE* fs);
boolean equality(Tree* tree1, Tree* tree2);

void listLeafNary(Tree* tree);
int lengthLeafNary(Tree* tree);
void successorNary(Tree* tree);
void indentNary(Tree* tree);
boolean predecessorNary(Tree* tree, Object* object);
void inWidthNary(Tree* tree);
Tree* dupTreeOnLevel(Tree* tree, int level, Object* (*toClone)(Object*));
void drawTreeNary(Tree* tree, FILE* fs);

void insertOrderTree(Tree* tree, Object* object);
Node* deleteOrderTree(Tree* tree, Object* object);
Node* searchInOrder(Tree* tree, Object* object);
Object* minOrderTree(Tree* tree);
Object* maxOrdertree(Tree* tree);

void insertinBalancedTree(Tree* tree, Object* object);


Node* cNd(char* msg, Node* left, Node* right);
Node* cF(char* msg);
Node* cFCh(char* msg);

Tree* createTreeCar(FILE* fe);

#endif