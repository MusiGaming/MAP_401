#ifndef _SIMPLIFICATION_BEZIER3_H_
#define _SIMPLIFICATION_BEZIER3_H_

#include "main.h"

Point Point_sur_bezier3 (Bezier3 B, double t);
double fonction_delta (double k, double n);
Bezier3 approx_bezier3(Liste_Point L, int j1, int j2);
double distance_point_bezier3 (Point P, Bezier3 B, double t);
Liste_Bezier3 simplification_douglas_peucker_Bezier3 (Liste_Point LP,int j1, int j2, double d);
Liste_Liste_Bezier3 TT_contour_en_Bezier3(Liste_Contour LC);
void esp_fichier_Bezier3(char nom[], Liste_Liste_Bezier3 LLB, UINT h, UINT l);

#endif