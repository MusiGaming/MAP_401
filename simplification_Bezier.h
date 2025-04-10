#ifndef _SIMPLIFICATION_BEZIER_H_
#define _SIMPLIFICATION_BEZIER_H_

#include "main.h"

Bezier2 approx_bezier2(Liste_Point L, int j1, int j2);
Point Point_sur_bezier2 (Bezier2 B, double t);
double dist_point_Bezier2 (Point P, Bezier2 B, double t);
Liste_Bezier2 simplification_douglas_peucker_bezier2 (Liste_Point LP, int j1, int j2, double d);
Bezier3 convertion_Bezier2_Bezier3(Bezier2 B2);
void esp_fichier_Bezier2(char nom[], Liste_Liste_Bezier2 LLB, UINT h, UINT l);
Liste_Liste_Bezier2 TT_contour_en_Bezier2(Liste_Contour LC);


#endif