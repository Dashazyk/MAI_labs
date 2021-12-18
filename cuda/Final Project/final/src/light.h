#ifndef LIGHT_H
#define LIGHT_H

#include "vect3.h"

struct Light {
	vect3 pos;
	vect3 col;
	double intensity;
};

Light make_light(vect3 pos, double intensity = 1);
Light make_light(vect3 pos, vect3 col, double intensity = 1);

void gen_light_circle(Light *lights, int light_cnt, double rad, double z, double intensity);

#endif 
