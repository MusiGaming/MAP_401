#ifndef _TACHES1_4_H_
#define _TACHES1_4_H_

#include "image.h"
#include "geom2d.h"
#include "conventions.h"

typedef enum {Nord, Est, Sud, Ouest} Orientation; 

void pixel(Pixel p);

void orientation(Orientation o);

Point trouver_pixel_depart(Image I);

void memoriser_position(FILE *f, Point position);

Point avancer(Point p, Orientation o, int k);

Orientation nouvelle_orientation(Image I, Point p, Orientation o);

#endif
