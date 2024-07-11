#include <stdio.h> // printf, FILE, fopen, fprintf
#include <stdlib.h> // malloc, free, exit
#include <string.h> // strlen
#include "screen.h"

// données locales au fichier ecran.cpp,
// inaccessibles pour l'utilisateur du module.
// static = locales au fichier pour les variables externes aux fonctions
static char* ecran; // pointeur sur le début de l'écran
static int nbLig; // nombre de lignes de l'écran
static int nbCol; // nombre de colonnes de l'écran
static int ncc; // numéro de colonne du crayon
static int nlc; // numéro de ligne du crayon
static int couleur; // couleur du crayon
// l'écran est un tableau de caractères ecran alloué dynamiquement
// de nl lignes sur nc colonnes et mis à blanc

void initialiserEcran (int nl, int nc) {
    nbLig = nl;
    nbCol = nc;
    ecran = (char*) malloc (nbLig * nbCol * sizeof(char));
    effacerEcran ();
}

// le crayon est mis en (nl, nc)
void crayonEn (int nl, int nc) {
    nlc = nl;
    ncc = nc;
}

// la couleur du dessin est c
void couleurCrayon (int c) {
    if (c>15) c = c % 16;
    couleur = c;
}

// écrire un caractère en fonction de la couleur en (nl, nc)
void ecrirePixel (int nl, int nc) {
    static char* tabCoul = "*123456789ABCDE.";
    if ( (nl>=0) && (nl<nbLig) && (nc>=0) && (nc<nbCol) )
    ecran [nl*nbCol+nc] = tabCoul [couleur];
}

// avancer dans la direction d de lg pixels
void avancer (int d, int n) {
 switch (d) {
    case DROITE:
        for (int i=ncc; i<ncc+n; i++) ecrirePixel (nlc, i);
        ncc += n-1;
        break;
    
    case HAUT:
        for (int i=nlc; i>nlc-n; i--) ecrirePixel (i, ncc);
        nlc += -n+1;
        break;
    case GAUCHE:
        for (int i=ncc; i>ncc-n; i--) ecrirePixel (nlc, i);
        ncc += -n+1;
        break;
    case BAS:
        for (int i=nlc; i<nlc+n; i++) ecrirePixel (i, ncc);
        nlc += n-1;
        break;
 } // switch
}

// tracer un rectangle défini par 2 points csg et cid
void rectangle (int xcsg, int ycsg, int xcid, int ycid) {
        int longueur = xcid-xcsg+1;
        int largeur = ycid-ycsg+1;
        crayonEn (ycsg, xcsg);
        avancer (BAS, largeur);
        avancer (DROITE, longueur);
        avancer (HAUT, largeur);
        avancer (GAUCHE, longueur);
}

// écrire un message à partir de (nl, nc)
void ecrireMessage (int nl, int nc, char* message) {
    for (int i=0; i<strlen(message); i++) {
        if ( (nl>=0) && (nl<nbLig) && (nc>=0) && (nc<nbCol) ) {
            ecran [nl*nbCol+nc] = message[i];
            nc++;
        }
    }
}

// afficher le dessin
void afficherEcran () {
    for (int i=0; i<nbLig; i++) {
        for (int j=0; j<nbCol; j++) printf ("%c", ecran [i*nbCol+j]);
        printf ("\n");
    }
    printf ("\n");
}
// mettre l'écran à blanc

void effacerEcran () {
    for (int i=0; i<nbLig; i++) {
        for (int j=0; j<nbCol; j++) ecran[i*nbCol+j] = ' ';
    }
    couleurCrayon (NOIR); // par défaut
    crayonEn (nbLig/2, nbCol/2); // milieu de l'écran
}

// rendre au système d'exploitation, l'espace alloué par
// malloc() dans initialiserEcran()
void detruireEcran () {
     free (ecran);
}

// sauver l'écran dans le fichier nomFS
void sauverEcran (char* nomFS) {
    FILE* fs = fopen (nomFS, "w");
    if (fs==NULL) { perror ("sauverEcran"); exit (1); };
    for (int i=0; i<nbLig; i++) {
        for (int j=0; j<nbCol; j++) fprintf (fs, "%c", ecran [i*nbCol+j]);
        fprintf (fs, "\n");
    }
    fprintf (fs, "\n");
    fclose (fs);
}