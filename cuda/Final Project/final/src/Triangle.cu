#include <stdio.h>
#include <stdlib.h>
#include "Triangle.h"
#include "color.h"


Triangle make_triangle(vect3 a, vect3 b, vect3 c, uchar4 color) {
	Triangle trig = {a, b, c, color};
	trig.normal = norm(prod(
		diff(trig.a, trig.c),
		diff(trig.a, trig.b)
	));
	return trig;
}

Triangle make_triangle(vect3 a, vect3 b, vect3 c, vect3 color) {
	return make_triangle(a, b, c, u4color(color));
}
