#include<stdio.h>               /* utilisation des entrees-sorties standard de C */
#include<stdlib.h>              /* utilisation des fonctions malloc et free */
#include <stdbool.h>            /* utilisation du type bool */
#include <string.h>             /* utilisation de manipulation des chaines de caractères*/

#include "main.h"            //Inclusion de notre fichier header

int main(int argc, char *argv[]){

    if (argc>2) {
        printf("Erreur nombre d'arguments");
        exit(999);
    }

    Image I = lire_fichier_image(argv[1]);
    Liste_Contour LC,LC2;
    LC = TT_Les_Contours(I);
    LC2 = TT_Contours_Simplifier_Douglas(LC);

    Liste_Liste_Bezier2 LB = TT_contour_en_Bezier2(LC2);

    esp_fichier_Bezier2(argv[1], LB, hauteur_image(I), largeur_image(I));
}