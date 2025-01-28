#include<stdlib.h>
#include<string.h>
#include <stdio.h>
#include "geom2d.h"

Point set_point (double x, double y){
    Point P = {x,y};
    return P;
}

Point add_point (Point P1, Point P2){
    return set_point(P1.x + P2.x , P1.y + P2.y);
}

Vecteur vect_bipoint (Point A, Point B){
    Vecteur V = {B.x - A.x , B.y - A.y};
    return V;
}

Vecteur somme2vecteurs (Vecteur A, Vecteur B){
    Vecteur V = {B.x + A.x , B.y + A.y};
    return V;
}


Vecteur produit_vecteur (Vecteur V, double a){
    Vecteur Vp = {a * V.x , a * V.y};
    return Vp;
}

Point produit_point (Point P, double a){
    Point Pp = {a * P.x, a * P.y};
    return Pp;
}

double produit_scalaire (Vecteur A, Vecteur B){
    return (A.x * B.x) + (A.y * B.y);
}

double norme_euclidienne (Vecteur V){
    return sqrt((V.x * V.x)+(V.y * V.y));
}

double distance (Point A, Point B){
    return sqrt(((A.x - B.x)*(A.x - B.x))+((A.y - B.y)*(A.y - B.y)));
}
