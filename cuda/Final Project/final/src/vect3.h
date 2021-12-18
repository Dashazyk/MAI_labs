#ifndef VECT3_H
#define VECT3_H

typedef struct {
	double x;
	double y;
	double z;
} vect3;

#define MIN(a, b) (a < b? a : b)

typedef unsigned char uchar;

__host__ __device__ double dot(vect3 a, vect3 b);
// as in, between two points with given coordinates
__host__ __device__ double distance(vect3 a, vect3 b) ;

// prod
__host__ __device__ vect3 prod(vect3 a, vect3 b);

__host__ __device__ vect3 norm(vect3 v);

__host__ __device__ vect3 diff(vect3 a, vect3 b);

__host__ __device__ vect3 add(vect3 a, vect3 b) ;
__host__ __device__ uchar4 add(uchar4 a, uchar4 b);

__host__ __device__ vect3 mult(vect3 a, vect3 b, vect3 c, vect3 v);

__host__ __device__ vect3 scale(vect3 v, double m);
__host__ __device__ uchar4 scale(uchar4 v, double m);

__host__ __device__ vect3 slide(vect3 pos, vect3 normdir, int mul=1);

__host__ __device__ double length(vect3 v);

__host__ __device__ void print(char *nm, vect3 v);

__host__ __device__ vect3 v2limits(vect3 value, vect3 down, vect3 upper);

#endif
