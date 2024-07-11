#include <stdio.h>
#include "screen.h"

void main () {
    initialiserEcran (20, 50);
    rectangle ( 3, 10, 43, 17); // maison
    rectangle ( 3, 4, 43, 10); // toiture
    rectangle (20, 12, 23, 17); // porte
    rectangle (41, 1, 43, 4); // cheminée
    rectangle (10, 12, 14, 15); // fenêtre gauche
    rectangle (30, 12, 34, 15); // fenêtre droite
    ecrireMessage (19, 15, "Maison de rêves");
    afficherEcran ();
    sauverEcran ("maison.res");
    detruireEcran ();
}