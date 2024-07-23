#include <stdio.h>
#include "..\list.h"
#include "people.h"

unsigned int menu(){
    printf("**************PEOPLE MANAGEMENT**************\n\n");
    printf("0. Quit\n");
    printf("1. Insert at the top\n");
    printf("2. Insert at the bottom\n");
    printf("3. Drop from the head\n");
    printf("4. Drop from the bottom\n");
    printf("5. Drop an element from its name\n");
    printf("6. List traversal\n");
    printf("7. Look for an element\n");
    printf("8. Ordered insertion from a file\n");
    printf("9. List destruction\n");

    unsigned int code;
    printf("\nMake a choice: ");
    scanf("%d", &code);

    return code;
}

int main(){
    List* lp = createList(UNORDERED, toStringPeople, comparePeople) ;
    boolean end = False;

    while(!end){
        switch(menu()){
            case 0:{
                end = True;
            }break;

            case 1:{
                People* one = createPeople();
                insertHead(lp, one);                
            }break;

            case 2:{
                People* one = createPeople();
                insertLast(lp, one);
            }break;

            case 3:{
                People* extract = (People*)extract_head(lp);
                if(extract==NULL){
                    printf("Empty list");
                }else{
                    printf("Dropped element %s %s from the top of list", extract->name, extract->surname);
                }                
            }break;

            case 4:{
                People* extract = (People*)extract_bottom(lp);
                if(extract==NULL){
                    printf("Empty list");
                }else{
                    printf("Dropped element %s %s from the bottom of list", extract->name, extract->surname);
                }
            }break;

            case 5:{
                printf("Name the element that you want to drop: ");
                ch15 name; scanf("%s", name);
                ch15 surname; scanf("%s", surname);
                People* one = createPeople(name, " ? ");
                People* found = (People*)search_object(lp, one);
                boolean extraction = extract(lp, found);
                if(extraction){
                    printf("%s %s has been dropped from the list",found->name, found->surname);
                }
            }break;

            case 6:{
                list(lp);
            }break;
            
            case 7:{
                printf("Name completely the one you are looking for: ");
                ch15 name; scanf("%s", name);
                ch15 surname; scanf("%s", surname);
                People* search= createPeople(name, surname);
                People* found = (People*)search_object(lp, search);
                if(found!=NULL){
                    printf("Element %s %s found", found->name, found->surname);
                }else{
                    printf("Element %s not found", search->name);
                }                
            }break;
            
            case 8:{
                printf("Name the file from where you want to load the datas: ");
                char* file_name; scanf("%s", &file_name);
                FILE* file = fopen(file_name, "r");
                
                if(file==NULL){
                    printf("This file doesn't exist.");
                }else{
                    printf("In which order do you want to order your list?\n");
                    printf("1. Growing order\n");
                    printf("2. Decreasing order\n");
                    unsigned int order;
                    printf("Select your order: "); scanf("%d",&order);

                    List* lp = createList(order, toStringPeople, comparePeople);
                    while(!feof(file)){
                        ch15 name, surname;
                        fscanf(file, "%s %s", name, surname);
                        People* index = createPeople(name, surname);
                        insert_inOrder(lp, index);
                    }
                    fclose(file);
                    list(lp);
                }                    
            }break;
            
            case 9:{
                destroy_list(lp);
            }break;            
                
                
        }
    }    
    return 0;
}