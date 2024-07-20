#include <stdio.h>
#include <stdlib.h>

#ifdef STACKARRAY_H
#include "stackArray.h" 
#else
#include "stack.h"
#endif

#include "numbers.h"

int menu(){
    printf("    **********************************STACK NUMBERS MANAGEMENT**********************************    \n");
    printf("\n");
    printf("0. Quit\n");
    printf("1. Stack Initialisation\n");
    printf("2. Is the stack empty ?\n");
    printf("3. Stack Insertion\n");
    printf("4. Stack Extraction\n");
    printf("5. List stack\n");
    printf("\n");
    
    int code;
    printf("Let's make a choice: ");
    scanf("%d", &code); getchar();
    printf("\n");

    return code;
}

int main(){
    #ifdef STACKARRAY
    #define LGMAX 7
    Stack* stack = createStack(LGMAX);
    #else
    Stack* stack = createStack();
    #endif

    boolean end = False;

    while(!end){
        int choice = menu();

        switch(choice){
            case 0:
                end = True;
            break;

            case 1:{
                destroyStack(stack);
                #ifdef STACKARRAY
                stack = createStack(LGMAX);
                printf("We deal with a stack which the length is %d", LGMAX);
                #else
                stack = createStack();
                #endif
            }break;
            
            case 2:
                printf((is_empty(stack))?"The stack is empty":"The stack is not empty");
            break;

            case 3:{
                printf("Which value do you want to be inserted? ");
                int value; scanf("%d", &value);
                stackin(stack,createInteger(value));

            }break;

            case 4:{
                Integer* i = (Integer*)stackout(stack);
                printf("The value %d has been dropped", i->value);
            }break;

            case 5:{
                listStack(stack, writeInteger);
            }break;

            default:
                printf("Make a real choice buddy");
            break;
        }
    }

    return 0;
}