#include <math.h>
#include "light.h"

Light make_light(vect3 pos, double intensity) {
	return make_light(pos, {1, 1, 1}, intensity);
}

Light make_light(vect3 pos, vect3 col, double intensity) {
	return {
		pos,
		col,
		intensity
	};
}

void gen_light_circle(Light *lights, int light_cnt, double rad, double z, double intensity) {
	int i;
	double dphi = M_PI * 2 / light_cnt;

	for (i = 0; i < light_cnt; ++i) {
		double lx = rad * cos(dphi * i);
		double ly = rad * sin(dphi * i);

		lights[i] = make_light(
			{lx, ly, z},
			//~ {cos(dphi * i)/2+0.5, sin(dphi * i)/2+0.5, 0.5},
			{(double)((i%3)==0), (double)((i%3)==1), (double)((i%3)==2)},
			intensity
		);
	}
}
