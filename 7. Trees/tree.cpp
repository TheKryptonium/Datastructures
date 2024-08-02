#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"
#include "..\4.List\list.h"

Node* getRoot(Tree* tree){
    return tree->root;
}

Object* getObject(Node* node){
    return node->reference;
}

void setRoot(Tree* tree, Node* root){
    tree->root=root;
}

void setString(Tree* tree, char* (*toString)(Object*)){
    tree->toString=toString;
}

void setCompare(Tree* tree, int (*compare)(Object*, Object*)){
    tree->toCompare=compare;
}

Node* getLeft(Node* node){
    return node->left;
}

Node* getRight(Node* node){
    return node->right;
}

static char* toChar(Object* object){
    return (char*)object;
}

static int compareCar(Object* object, Object* object2){
    return strcmp(toChar(object), toChar(object2));
}

static int max(int str1, int str2){
    return (str1> str2)==1? str1:str2;
}

Node* cNd(Object* object, Node* left, Node* right){
    Node* node= new Node();
    node->reference=object;
    node->right=right;
    node->left=left;
    return node;
}

Node* cNd(Object* object){
    return cNd(object,NULL,NULL);
}

Node* cF(Object* object){
    return cNd(object);
}

void initTree(Tree* tree, Node* root, char* (*toString)(Object*), int (*toCompare)(Object*,Object*)){
    tree->root=root;
    tree->toString=toString;
    tree->toCompare=toCompare;
}

Tree* createTree(Node* root, char* (*toString)(Object*), int (*toCompare)(Object*,Object*)){
    Tree* tree = new Tree();
    initTree(tree, root, toString, toCompare);
    return tree;
}

Tree* createTree(Node* root){
    return createTree(root, toChar, compareCar);
}

Tree* createTree(){
    return createTree(NULL, toChar, compareCar);
}

boolean is_empty(Tree* tree){
    return (tree->root==NULL);
}

Node* cF(char* message){
    return cF((Object*)message);
}

Node* cNd(char* message, Node* left, Node* right){
    return cNd((Object*)message, left, right);
}

Tree* Genealogical(){
    Node* root=cNd("Julie", 
                        cNd("Johny",
                            cNd("Paula",NULL,
                            cNd("Sonia",NULL,
                            cF("Paul"))),
                        cNd("Gontran",
                            cF("Tony"),NULL)),
                    NULL
                );
    return createTree(root);
}

Tree* Arithmetical(){ /*Sequential tree: ((a+b)*(c-d))-e*/
    Node* root= cNd("-",
                        cNd("*",
                                cNd("+",cF("a"),cF("b")),
                                cNd("-",cF("c"),cF("d"))),
                        cF("e")
                    );
    return createTree(root);
}

void prefix(Node* root, char* (*toString)(Object*)){
    if(root!=NULL){
        printf("%s", toString(root->reference));
        prefix(root->left, toString);
        prefix(root->right, toString);
    }
}

void prefix(Tree* tree){
    prefix(tree->root,tree->toString);
}

void infix(Node* root, char* (*toString)(Object*)){
    if(root!=NULL){
        infix(root->left,toString);
        printf("%s",toString(root->reference));
        infix(root->right, toString);
    }
}

void infix(Tree* tree){
    infix(tree->root, tree->toString);
}

void postfix(Node* root, char* (*toString)(Object*)){
    if(root!=NULL){
        postfix(root->left, toString);
        postfix(root->right, toString);
        printf("%s", toString(root->reference));
    }
}

void postfix(Tree* tree){
    postfix(tree->root, tree->toString);
}

static void indentPrefix(Node* root, char* (*toString)(Object*), int level){
    if(root!=NULL){
        printf("\n");
        for(int j=1;j<level;j++)printf("%5s", " ");
        printf("%s", toString(root->reference));
        indentPrefix(root->left, toString, level+1);
        indentPrefix(root->right, toString, level+1);
    }
}

void indentPrefix(Tree* tree){
    indentPrefix(tree->root, tree->toString, 1);
}

static void indentInfix(Node* root, char* (*toString)(Object*), int level){
    if(root!=NULL){
        printf("\n");
        for(int i=1; i<level;i++) printf("%5s", " ");
        indentInfix(root->left, toString, level+1);
        printf("%s", toString(root));
        indentInfix(root->right, toString, level+1);
    }
}

void indentInfix(Tree* tree){
    indentInfix(tree->root, tree->toString, 1);
}

static void indentPostfix(Node* root, char* (*toString)(Object*), int level){
    if(root!=NULL){
        printf("\n");
        for(int j=1; j<level; j++) printf("\n");
        indentPostfix(root->left, toString, level+1);
        indentPostfix(root->right, toString, level+1);
        printf("%s", toString(root->reference));
        
    }
}

void indentPostfix(Tree* tree){
    indentPostfix(tree->root, tree->toString, 1);
}

static Node* searchNode(Node* root, Object* object, int (*compare)(Object*, Object*)){
    if(root==NULL){
        return NULL;
    }else if(compare(root->reference, object)==0){
        return root;
    }else {
        Node* found=searchNode(root->left, object, compare);
        if(found==NULL) searchNode(root->right, object, compare);
        return found;
    }
}

Node* searchNode(Tree* tree, Object* object){
    return searchNode(tree->root, object, tree->toCompare);
}

static void inWidth(Node* root, char* (*toString)(Object*)){
    List* li = createList();
    insertLast(li, root);
    
    while(!EOList(li)){
        Node* extract = (Node*)extract_head(li);
        printf("%s", toString(extract));
       
        if(extract->left!=NULL)  insertLast(li, extract->left);
        if(extract->right!=NULL) insertLast(li, extract->right);
    }
}

void inWidth(Tree* tree){
    inWidth(tree->root, tree->toString);
}

int length(Node* root){
    if(root==NULL){
        return 0;
    }else{
        return 1+length(root->left)+length(root->right);
    }
}

int length(Tree* tree){
    return length(tree->root);
}


boolean isLeaf(Node* node){
    return (node->left==NULL && node->right==NULL);
}

static int  leafLength(Node* root){
    if(root==NULL){
        return 0;
    }else if(leafLength(root)){
        return 1;
    }else{
        return leafLength(root->left)+leafLength(root->right);
    }
}

int leafLength(Tree* tree){
    return leafLength(tree->root);
}

static void listLeaf(Node* root, char* (*toString)(Object*)){
    if(root!=NULL){
        if(isLeaf(root)){
            printf("%s\n", toString(root->reference));
        }else{
            listLeaf(root->left, toString);
            listLeaf(root->right, toString);
        }
    }
}

void listLeaf(Tree* tree){
    listLeaf(tree->root, tree->toString);
}

static int maxIdent(Node* root, char* (*toString)(Object*)){
    int lg;
    if(root==NULL){
        lg=0;
    }else{
        lg=max(maxIdent(root->left, toString), maxIdent(root->right, toString));
        lg =max(lg, strlen(toString(root->reference)));
    }
    return lg;
}

int maxIdent(Tree* tree){
    return maxIdent(tree->root, tree->toString);
}

static int lgIdent(Node* root, char* (*toString)(Object*)){
    int lg;
    if(root==NULL){
        lg=0;
    }else{
        lg=lgIdent(root->left, toString)+lgIdent(root->right, toString)+strlen(toString(root->reference));
    }
    return lg;
}

int lgIdent(Tree* tree){
    return lgIdent(tree->root, tree->toString);
}


static int height(Node* root){
    if(root==NULL){
        return 0;
    }else{
        return 1+ max(height(root->left), height(root->right));
    }
}

int height(Tree* tree){
    return height(tree->root);
}

static boolean degenerated(Node* root){
    boolean d;
    if(root==NULL){
        d=False;
    }else{
        if(isLeaf(root)){
            d=True;
        }else if(root->left!=NULL && root->right!=NULL){
            d=False;
        }else if(root->right==NULL){
            d=degenerated(root->left);
        }else{
            d=degenerated(root->right);
        }
    }
    return d;
}


boolean degenerated(Tree* tree){
    return degenerated(tree->root);
}

static Node* copyTree(Node* root, Object* (*toClone)(Object*)){
    if(root==NULL){
        return NULL;
    }else{
        Node* rt = cNd(root->reference);
        rt->left=copyTree(root->left, toClone);
        rt->right=copyTree(root->right, toClone);
        return rt;
    }
}

Tree* copyTree(Tree* tree, Object* (*toClone)(Object*)){
    Node* root= copyTree(tree->root, toClone);
    return createTree(root, tree->toString, tree->toCompare);
}

static void destroyTree(Node** root){
    Node* rt= *root;
    if(rt!=NULL){
        destroyTree(&rt->right);
        destroyTree(&rt->left);
        free(rt);
        *root=NULL;
    }
}

void destroyTree(Tree* tree){
    destroyTree(&tree->root);
}

static boolean equality(Node* root1, Node* root2, int (*compare)(Object*, Object*)){
    boolean result=False;
    if(root1==NULL && root2==NULL){
        result=True;
    }else if(root1!=NULL && root2!=NULL){
        if(compare(root1->reference, root2->reference)==1){
            if(equality(root1->left, root2->left, compare)==1){
                result=equality(root2->right, root2->right, compare);
            }
        }
    }
    return result;
}

boolean equality(Tree* tree1, Tree* tree2){
    return equality(tree1->root, tree2->root, tree1->toCompare);
}

typedef struct{
    char* message;
    int position;
}NomPos;

int posNdc=0;

static Node* dupTree(Node* root, char* (*toString)(Object*)){
    if(root==NULL){
        return NULL;
    }else{
        Node* node = new Node();
        NomPos* object = new NomPos();
        node->reference=object;
        object->message=toString(root->reference);
        node->left=dupTree(root->left, toString);
        int lg = strlen(toString(root->left->reference));
        object->position=posNdc+lg/2;
        posNdc +=lg;
        node->right= dupTree(root->right, toString);
        return node;
    }
}

static Tree* dupTree(Tree* tree){
    posNdc=0;
    Node* node = dupTree(tree->root, tree->toString);
    return createTree(node, tree->toString, NULL);
}



void drawTree(Tree* tree, FILE* fs){
    if(is_empty(tree)){
        printf("Your tree is empty");
        return;
    }
    int lg = lgIdent(tree);
    char* line = (char*)malloc(lg+1);
    line[lg] = 0;

    Tree* tr = dupTree(tree);

    List* current=createList();
    insertHead(current, tr->root);
    List* next= createList();

    while(!is_empty(current)){
        for(int i=0; i<lg;i++) line[i]=' ';
        openList(current);
        while(!EOList(current)){
            Node* ptNd=(Node*)current_object(current);
            NomPos* ptc = (NomPos*)ptNd->reference;
            line[ptc->position]='|';
        }

        for(int i=1; i<=2;i++) fprintf(fs, "%s\n", line);

        for(int j=0; j<lg; j++) line[j]=' ';

        while(!EOList(current)){
            Node* pNc=(Node*)extract_head(current);
            Node* left=pNc->left;
            Node* right = pNc->right;
            char* message = ((NomPos*)pNc->reference)->message;
            int lg = strlen(message);
            int position = ((NomPos*)pNc->reference)->position;
            int posNom = position-lg/2;
            int leftPos= left==NULL? position:((NomPos*)left->reference)->position;
            int rightPos=right==NULL?position:((NomPos*)right->reference)->position;

            if(left!=NULL) insertLast(next, left);
            if(right!=NULL) insertLast(next, right);


            for(int i=leftPos; i<rightPos; i++) line[i]='_';
            for(int j=0;j<lg;j++) line[posNom+j]=message[j];
        }

            fprintf(fs,"%s", line);
            copy_list(current, next);
    }
    destroyTree(tr);
}

static void listLeafNary(Node* root, char* (*toString)(Object*)){
    if(root!=NULL){
        if(root->left==NULL) printf("%s\n", toString(root->reference));
        listLeaf(root->left, toString);
        listLeaf(root->right, toString);
    }
}

void listLeafNary(Tree* tree){
    if(tree->root!=NULL){
        Node* node =cNd(tree->root->reference, tree->root->left, NULL);
        Tree* tr = createTree(node, tree->toString, NULL);
        listLeafNary(tr->root, tr->toString);
        free(node);
        free(tr);
    }
}

static int lengthLeafNary(Node* root){
    int n=0;
    if(root==NULL){
        return 0;
    }else{
        if(root->left==NULL) n =1;
        return n+lengthLeafNary(root->left)+lengthLeafNary(root->right);
    }
}

int lengthLeafNary(Tree* tree){
    int n=0;
    if(tree->root!=NULL){
        Node* node=cNd(tree->root->reference, tree->root->left, NULL);
        Tree* tr=createTree(node, tree->toString, NULL);
        n=lengthLeafNary(tr->root);
        free(node);
        free(tr);
    }
    return n;
}


static void successorNary(Node* root, char* (*toString)(Object*)){
    if(root!=NULL){
        if(root->left==NULL){
            printf("Any succesor for %s\n", toString(root->reference));
        }else{
            prefix(root->left, toString);
        }
    }
}

void successorNary(Tree* tree){
    successorNary(tree->root, tree->toString);
}

static void indentNary(Node* root, char* (*toString)(Object*), int level){
    if(root!=NULL){
        for(int j=0; j<level;j++) printf("%5s", " ");
        printf("%s\n", toString(root->reference));
        indentNary(root->left, toString, level+1);
        indentNary(root->right, toString, level);
    }
}

void indentNary(Tree* tree){
    if(tree->root!=NULL){
        Node* node = cNd(tree->root->reference, tree->root->left, NULL);
        Tree* tr= createTree(node, tree->toString, NULL);
        indentNary(tr->root, tr->toString,1);
        free(node);
        free(tr);
    }
}

static boolean predecessorNary(Node* root, Object* object, char* (*toString)(Object*), int (*compare)(Object*, Object*)){
    boolean found;
    if(root==NULL){
        found=False;
    }else if(compare(object, root->reference)==0){
        printf("%s",toString(root->reference));
        found =True;
    }else{
        predecessorNary(root->left, object, toString, compare);
        if(found){
            printf("%s", toString(root->reference));
        }else{
            predecessorNary(root->right, object, toString, compare);
        }
    }
    return found;
}

boolean predecessorNary(Tree* tree, Object* object){
    return predecessorNary(tree->root, object, tree->toString, tree->toCompare);
}

static void inWidthNary(Node* root, char* (*toString)(Object*)){
    List* li=createList();
    insertLast(li, root->reference);
    while(!is_empty(li)){
        Node* extract =(Node*)extract_head(li);
        Node* first = extract->left;
        if(first!=NULL) printf("%s: ", toString(root->reference));
        Node* bro = first;
        while(bro!=NULL){
            printf(" %s", toString(bro->reference));
            insertLast(li, bro);
            bro=bro->right;
        }
        if(first!=NULL) printf(";\n");
    }
}

void inWidthNary(Tree* tree){
    Node* node = cNd(tree->root->reference,tree->root->left, NULL);
    Tree* tr= createTree(node, tree->toString, NULL);
    inWidthNary(tr->root, tree->toString);
    free(node);
    free(tr);
}

static Node* dupTreeOnLevel(Node* root, int nblevel, Object* (*toClone)(Object*)){
    if(root==NULL || nblevel==0){
        return NULL;
    }else{
        Node* node = cNd(toClone(root->reference));
        node->left=dupTreeOnLevel(node->left, nblevel-1, toClone);
        node->right=dupTreeOnLevel(node->right, nblevel, toClone);
        return node;
    }
}

Tree* dupTreeOnLevel(Tree* tree, int nblevel, Object* (*toClone)(Object*)){
    return createTree(dupTreeOnLevel(tree->root, nblevel, toClone));
}

