#ifndef RENDER_H
#define RENDER_H

#include "vect3.h"
#include "Triangle.h"
#include "light.h"

__global__ void raytrace(Triangle *triags, int trig_cnt, Light *light, int light_cnt, vect3 ambient, vect3 pc, vect3 pv, int w, int h, double angle, uchar4 *data);
__global__ void antiaaliasing(uchar4 *data, uchar4 *odata, int w, int h, int r);
void cpu(
	Triangle *triags, int trig_cnt,
	Light *light, int light_cnt,
	vect3 ambient,
	vect3 pc, vect3 pv,
	int w, int h,
	double angle, uchar4 *data
);
#endif
