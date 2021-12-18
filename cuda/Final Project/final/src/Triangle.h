#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vect3.h"

struct Triangle {
	vect3 a;
	vect3 b;
	vect3 c;
	uchar4 color;
	vect3 normal;
};

Triangle make_triangle(vect3 a, vect3 b, vect3 c, uchar4 color);
Triangle make_triangle(vect3 a, vect3 b, vect3 c, vect3  color);

#endif
