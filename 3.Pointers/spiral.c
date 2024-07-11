#include <stdio.h>
#include "screen.h"

#define WIDTH 50
#define HEIGHT 50
#define CENTER_W WIDTH/2
#define CENTER_H HEIGHT/2

void spiral(int n, int lgMax){
    
    if(n<=lgMax){
       avancer(DROITE,n);
       avancer(HAUT,n+1);
       avancer(GAUCHE,n+2);
       avancer(BAS,n+3);
       spiral(n+4,lgMax);
    }
}

int main(){
    initialiserEcran (WIDTH, HEIGHT);
    crayonEn(CENTER_W,CENTER_H);
    spiral(3,WIDTH-3);
    afficherEcran();
    detruireEcran();
    detruireEcran();
    return 0;
}