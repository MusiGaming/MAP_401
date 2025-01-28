#ifndef _GEOM2D_H_
#define _GEOM2D_H_

#include <math.h>

typedef struct Vecteur {
    double x,y ; //coordonnees
} Vecteur;

typedef struct Point {
    double x,y ; //coordonnees
} Point;


Point set_point (double x, double y);

Point add_point (Point P1, Point P2);

Vecteur vect_bipoint (Point A, Point B);

Vecteur somme2vecteurs (Vecteur A, Vecteur B);

Vecteur produit_vecteur (Vecteur V, double a);

Point produit_point (Point P, double a);

double produit_scalaire (Vecteur A, Vecteur B);

double norme_euclidienne (Vecteur V);

double distance (Point A, Point B);


#endif 
