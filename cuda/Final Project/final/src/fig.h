#ifndef FIG_H
#define FIG_H

#include "Triangle.h"
#include "color.h"

struct Figure {
	Triangle *triags;
	int triag_count;
};

Figure gen_floor(vect3 color, vect3 *points);
Figure gen_icosa(vect3 color, vect3 pos, double radius);
Figure gen_hex  (vect3 color, vect3 pos, double rad);
Figure gen_dodec(vect3 color, vect3 pos, double rad);

#endif
