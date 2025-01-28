#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"image.h"

int main (int argc, char *argv[]){
    
    //verifier nombre d'arguments:
    if (argc != 2){
        printf("Erreur nombre d'arguments !");
        return 1;
    }

    //tester fonction lire_fichier_image:
    Image I;
    I = lire_fichier_image (argv[1]);

    //tester fonction ecrire_image:
    printf("Image I: \n");
    ecrire_image(I);
    printf("\n");

    //tester fonction negatif_image:
    Image I_neg = negatif_image (I);
    printf("Image négative de I: \n");
    ecrire_image(I_neg);
    printf("\n");

    return 0;

}