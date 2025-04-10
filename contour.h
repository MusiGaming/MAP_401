#ifndef _CONTOUR_H_
#define _CONTOUR_H_

#include "image.h"
#include "geom2d.h"
#include "conventions.h"
#include "list_contour.h"
#include "list_bezier2.h"

typedef enum {Nord, Est, Sud, Ouest} Orientation; 

void ecrire_pixel(Pixel p);

void ecrire_orientation(Orientation o);

Point trouver_pixel_depart(Image I);

Point avancer(Point p, Orientation o, int k);

Orientation tourner_robot(Orientation o, int deg);

Orientation nouvelle_orientation(Image I, Point p, Orientation o);

Contour memoire_sous_fichier(Image I, Point P, Point pos, Orientation O);

void eps_fichier(FILE *file, Contour C, UINT h, UINT l);
void esp_fichier_tt_contours(char nom[], Liste_Contour LC, UINT h, UINT l);

bool image_vide(Image I);
Image Image_calque(Image I);

Liste_Contour TT_Les_Contours(Image I);
double dist_seg(Point A, Point B, Point P);

Liste_Point simplification_douglas_peucker(Contour C, int j1, int j2, double d);
Liste_Contour TT_Contours_Simplifier_Douglas(Liste_Contour LC);

int nb_points(Liste_Contour LC);
#endif
