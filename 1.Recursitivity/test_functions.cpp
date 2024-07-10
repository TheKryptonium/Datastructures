#include <iostream>
#include "basics.h"

using namespace std;

int main(){
    unsigned int operation; int number, a, b, pow;

    cout<<"MENU"<<endl;
    cout<<"\n"<<endl;
    cout<<"------------------------------------------------------------------"<<endl;
    cout<<"1. Factorial"<<endl;
    cout<<"2. Fibonnaccci"<<endl;
    cout<<"3. Decreasing loop"<<endl;
    cout<<"4. Increasing loop"<<endl;
    cout<<"5. Convert in base 10"<<endl;
    cout<<"6. Convert in base b from 10"<<endl;
    cout<<"7. Convert from a base A to base B"<<endl;
    cout<<"8. Power the number"<<endl;
    cout<<"9. Let's play with Hanoi tower"<<endl;
    cout<<"------------------------------------------------------------------"<<endl;
    cout<<"\n"<<endl;
    cout<<"Select your operation by typing the corresponding number: "; cin>>operation;
    switch(operation){
        case 1:
            cout<<"Choose an integer: "; cin>>number;
            cout<<"The factorial of "<<number<<" is: "<<factorial(number);
            break;

        default:
            cout<<"Choose another option"<<endl;
            break;
        
    }

    return 0;
}