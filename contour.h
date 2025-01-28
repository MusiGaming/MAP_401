#ifndef _CONTOUR_H_
#define _CONTOUR_H_

#include "image.h"
#include "geom2d.h"

typedef enum {Nord, Est, Sud, Ouest} Orientation; 

void pixel(Pixel p);

void orientation(Orientation o);

Point trouver_pixel_depart(Image I);

void memoriser_position(Point position);

Point avancer(Point p, Orientation o, int k);

Orientation nouvelle_orientation(Image I, Point p, Orientation o);

#endif
