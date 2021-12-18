#include "Triangle.h"
#include "color.h"

typedef unsigned char uchar;

__host__ __device__ uchar4 u4color(vect3 v) {
	return {
		(uchar)(v.x * 255),
		(uchar)(v.y * 255),
		(uchar)(v.z * 255),
		255
	};
}
