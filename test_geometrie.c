#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"geom2d.h"

int main (int argc, char *argv[]){

    double x1, y1, x2, y2, a; 

    x1 = 1.0;
    y1 = 4.5;
    x2 = 2.5;
    y2 = -3.0;
    a = 2.0;

    Point P1 = set_point (x1, y1);
    Point P2 = set_point (x2, y2);

    Point P3 = add_point (P1, P2);

    Vecteur V1 = vect_bipoint (P1, P2);

    Vecteur V2 = vect_bipoint (P1, P3);

    Vecteur V_somme = somme2vecteurs (V1, V2);

    Vecteur V_multip = produit_vecteur (V1, a);

    Point P_multip = produit_point (P1, a);

    double P_sca = produit_scalaire (V1, V2);

    double norme = norme_euclidienne (V1);

    double dis = distance (P1, P2);

    printf("On pose les points (%.2lf , %.2lf)et (%.2lf , %.2lf) \n", P1.x, P1.y, P2.x, P2.y);
    printf("la somme de ces points est: (%.2lf , %.2lf) \n", P3.x, P3.y);
    printf("On definit les vecteurs (%.2lf , %.2lf)et (%.2lf , %.2lf) \n", V1.x, V1.y, V2.x, V2.y);
    printf("la somme de ces vecteurs est: (%.2lf , %.2lf) \n", V_somme.x, V_somme.y);
    printf("la multiplication avec un scalaire du point: (%.2lf , %.2lf) \n", P_multip.x, P_multip.y);
    printf("la multiplication avec un scalaire du vecteur: (%.2lf , %.2lf) \n", V_multip.x, V_multip.y);
    printf("le produit scalaire est : %.2lf \n", P_sca);
    printf("la norme euclidienne du vecteur est : %.2lf \n", norme);
    printf("la distance entre 2 points est: %.2lf \n", dis);
    
}