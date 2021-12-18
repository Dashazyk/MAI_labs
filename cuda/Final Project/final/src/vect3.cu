#include <stdio.h>
#include "vect3.h"

__host__ __device__ double dot(vect3 a, vect3 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

// prod
__host__ __device__ vect3 prod(vect3 a, vect3 b) {
	return {
		a.y * b.z - a.z * b.y, 
		a.z * b.x - a.x * b.z, 
		a.x * b.y - a.y * b.x
	};
}

__host__ __device__ vect3 norm(vect3 v) {
	double l = sqrt(dot(v, v));
	return {
		v.x / l, 
		v.y / l, 
		v.z / l
	};
}

__host__ __device__ vect3 diff(vect3 a, vect3 b) {
	return {a.x - b.x, a.y - b.y, a.z - b.z};
}

__host__ __device__ vect3 add(vect3 a, vect3 b) {
	return {a.x + b.x, a.y + b.y, a.z + b.z};
}
__host__ __device__ uchar4 add(uchar4 a, uchar4 b) {
	return {
		(uchar)MIN((int)a.x + b.x, 255), 
		(uchar)MIN((int)a.y + b.y, 255),
		(uchar)MIN((int)a.z + b.z, 255),
		(uchar)MIN((int)a.w + b.w, 255)
	};
}

__host__ __device__ vect3 mult(vect3 a, vect3 b, vect3 c, vect3 v) {
	return {
		a.x * v.x + b.x * v.y + c.x * v.z,
		a.y * v.x + b.y * v.y + c.y * v.z,
		a.z * v.x + b.z * v.y + c.z * v.z
	};
}

__host__ __device__ vect3 scale(vect3 v, double m) {
	return {v.x * m, v.y * m, v.z * m};
}
__host__ __device__ uchar4 scale(uchar4 v, double m) {
	return {
		(uchar)(v.x * m), 
		(uchar)(v.y * m), 
		(uchar)(v.z * m), 
		(uchar)(v.w * m)
	};
}

__host__ __device__ double length(vect3 v) {
	//~ return sqrt(dot(v, v));
	return sqrt(v.x * v.x + v.y*v.y + v.z * v.z);
}

__host__ __device__ void print(char *nm, vect3 v) {
	printf("%s (%g; %g; %g)\n", nm, v.x, v.y, v.z);
}

__host__ __device__ double dbl2limits(double value, double down, double upper) {
	return (upper - down)/1.0 * value + down;
}

__host__ __device__ vect3 v2limits(vect3 value, vect3 down, vect3 upper) {
	return {
		dbl2limits(value.x, down.x, upper.x),
		dbl2limits(value.y, down.y, upper.y),
		dbl2limits(value.z, down.z, upper.z)
	};
}
