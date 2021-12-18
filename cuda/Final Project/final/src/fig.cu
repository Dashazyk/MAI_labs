#include <stdio.h>
#include "fig.h"

Figure gen_floor(vect3 color, vect3 *points) {
	Figure f;

	f.triag_count = 2;
	f.triags = (Triangle *)malloc(sizeof(Triangle) * f.triag_count);
	
	f.triags[0] = make_triangle(points[1], points[0], points[2], color);
	f.triags[1] = make_triangle(points[0], points[1], points[3], color);

	return f;
}

Figure gen_icosa(vect3 color, vect3 pos, double rad) {
	Figure f;

	f.triag_count = 20;
	f.triags = (Triangle *)malloc(sizeof(Triangle) * f.triag_count);
	
    vect3 v[12];
	float X=.525731112119133606f;
	float Z=.850650808352039932f;
	float N=0.f;


	fprintf(stderr, "%s (%g) ", __FUNCTION__, rad);
	//~ print(pos);
	fprintf(stderr, "=======\n");

	v[0]  = {-X, N, Z};
	v[1]  = { X, N, Z};
	v[2]  = {-X, N,-Z};
	v[3]  = { X, N,-Z};
	v[4]  = { N, Z, X};
	v[5]  = { N, Z,-X};
	v[6]  = { N,-Z, X};
	v[7]  = { N,-Z,-X};
	v[8]  = { Z, X, N};
	v[9]  = {-Z, X, N};
	v[10] = { Z,-X, N};
	v[11] = {-Z,-X, N};
	
    for (int i = 0; i < 12; i++)
		v[i] = add(scale(v[i], rad), pos);
    
	f.triags[ 0] = make_triangle(v[ 0], v[ 4], v[ 1], color);
	f.triags[ 1] = make_triangle(v[ 0], v[ 9], v[ 4], color);
	f.triags[ 2] = make_triangle(v[ 9], v[ 5], v[ 4], color);
	f.triags[ 3] = make_triangle(v[ 4], v[ 5], v[ 8], color);
	f.triags[ 4] = make_triangle(v[ 4], v[ 8], v[ 1], color);
	f.triags[ 5] = make_triangle(v[ 8], v[10], v[ 1], color);
	f.triags[ 6] = make_triangle(v[ 8], v[ 3], v[10], color);
	f.triags[ 7] = make_triangle(v[ 5], v[ 3], v[ 8], color);
	f.triags[ 8] = make_triangle(v[ 5], v[ 2], v[ 3], color);
	f.triags[ 9] = make_triangle(v[ 2], v[ 7], v[ 3], color);
	f.triags[10] = make_triangle(v[ 7], v[10], v[ 3], color);
	f.triags[11] = make_triangle(v[ 7], v[ 6], v[10], color);
	f.triags[12] = make_triangle(v[ 7], v[11], v[ 6], color);
	f.triags[13] = make_triangle(v[11], v[ 0], v[ 6], color);
	f.triags[14] = make_triangle(v[ 0], v[ 1], v[ 6], color);
	f.triags[15] = make_triangle(v[ 6], v[ 1], v[10], color);
	f.triags[16] = make_triangle(v[ 9], v[ 0], v[11], color);
	f.triags[17] = make_triangle(v[ 9], v[11], v[ 2], color);
	f.triags[18] = make_triangle(v[ 9], v[ 2], v[ 5], color);
	f.triags[19] = make_triangle(v[ 7], v[ 2], v[11], color); 

	return f;
}

Figure gen_hex(vect3 color, vect3 pos, double rad) {
	Figure f;
	
	f.triag_count = 16;
	f.triags = (Triangle *)malloc(sizeof(Triangle) * f.triag_count);
	//~ memset(f.triags, 0, sizeof(Triangle) * f.triag_count);

	fprintf(stderr, "%s (%g)\n", __FUNCTION__, rad);
	//~ print(pos);

	vect3 ft = { 0,  1,  0};
	vect3 bk = { 0, -1,  0};
	vect3 tp = { 0,  0,  1};
	vect3 bm = { 0,  0, -1};
	vect3 lt = {-1,  0,  0};
	vect3 rt = { 1,  0,  0};

	//~ ft = add(scale(ft, rad), pos);
	//~ bk = add(scale(bk, rad), pos);
	//~ tp = add(scale(tp, rad), pos);
	//~ bm = add(scale(bm, rad), pos);
	//~ lt = add(scale(lt, rad), pos);
	//~ rt = add(scale(rt, rad), pos);

	vect3 lt_ft_tp = add(add(lt, ft), tp);
	vect3 lt_ft_bm = add(add(lt, ft), bm);
	
	vect3 lt_bk_tp = add(add(lt, bk), tp);
	vect3 lt_bk_bm = add(add(lt, bk), bm);
	
	vect3 rt_ft_tp = add(add(rt, ft), tp);
	vect3 rt_ft_bm = add(add(rt, ft), bm);
	
	vect3 rt_bk_tp = add(add(rt, bk), tp);
	vect3 rt_bk_bm = add(add(rt, bk), bm);

	rad /= sqrt(3);
	lt_ft_tp = add(scale(lt_ft_tp, rad), pos);
	lt_ft_bm = add(scale(lt_ft_bm, rad), pos);
	
	lt_bk_tp = add(scale(lt_bk_tp, rad), pos);
	lt_bk_bm = add(scale(lt_bk_bm, rad), pos);
	
	rt_ft_tp = add(scale(rt_ft_tp, rad), pos);
	rt_ft_bm = add(scale(rt_ft_bm, rad), pos);
	
	rt_bk_tp = add(scale(rt_bk_tp, rad), pos);
	rt_bk_bm = add(scale(rt_bk_bm, rad), pos);

	f.triags[ 0] = make_triangle(lt_ft_bm, lt_ft_tp, rt_ft_tp, color);
	f.triags[ 1] = make_triangle(lt_ft_bm, rt_ft_bm, rt_ft_tp, color);
	
	f.triags[ 2] = make_triangle(lt_ft_tp, lt_bk_tp, rt_ft_tp, color);
	f.triags[ 3] = make_triangle(rt_bk_tp, lt_bk_tp, rt_ft_tp, color);
	
	f.triags[ 4] = make_triangle(lt_ft_bm, lt_bk_bm, rt_ft_bm, color);
	f.triags[ 5] = make_triangle(rt_bk_bm, lt_bk_bm, rt_ft_bm, color);

	f.triags[ 6] = make_triangle(lt_bk_bm, lt_bk_tp, rt_bk_tp, color);
	f.triags[ 7] = make_triangle(lt_bk_bm, rt_bk_bm, rt_bk_tp, color);
	
	f.triags[ 8] = make_triangle(lt_ft_tp, lt_ft_bm, lt_bk_tp, color);
	f.triags[ 9] = make_triangle(lt_bk_tp, lt_bk_bm, lt_ft_bm, color);
	
	f.triags[10] = make_triangle(rt_ft_tp, rt_ft_bm, rt_bk_tp, color);
	f.triags[11] = make_triangle(rt_bk_tp, rt_bk_bm, rt_ft_bm, color);

	//~ print(tp);
	//~ print(bm);
	
	//~ print(lt_ft_bm);
	//~ print(rt_bk_tp);
	fprintf(stderr, "=======\n");
	//~ f.triags[] = make_triangle(, color);
	//~ f.triags[] = make_triangle(, color);
	//~ f.triags[] = make_triangle(, color);
	//~ f.triags[] = make_triangle(, color);
	//~ f.triags[] = make_triangle(, color);
	//~ f.triags[] = make_triangle(, color);

	return f;
}

Figure gen_dodec(vect3 color, vect3 pos, double rad) {
	Figure f;
	f.triag_count = 37;
	f.triags = (Triangle *)malloc(sizeof(Triangle) * f.triag_count);

	fprintf(stderr, "%s (%g) ", __FUNCTION__, rad);
	//~ print(pos);
	fprintf(stderr, "=======\n");
	
	float u = 2 / (sqrtf(5) + 1), p = (sqrtf(5) + 1)/2;

    //std::cout << "p - " << p << "\n";
    //std::cout << "u - " << u << "\n";

    vect3 v[20] = {
		vect3{-u, 0, p},   vect3{u, 0, p},
		vect3{-1, 1, 1},   vect3{1, 1, 1},
		vect3{1, -1, 1},   vect3{-1, -1, 1},
		vect3{0, -p, u},   vect3{0, p, u},
		vect3{-p, -u, 0},  vect3{-p, u, 0},
		vect3{p, u, 0},    vect3{p, -u, 0},
		vect3{0, -p, -u},  vect3{0, p, -u},
		vect3{1, 1, -1},   vect3{1, -1, -1},
		vect3{-1, -1, -1}, vect3{-1, 1, -1},
		vect3{u, 0, -p},   vect3{-u, 0, -p}
    };

    for (int i = 0; i < 20; i++) {
        v[i].x /= sqrt(3);
        v[i].y /= sqrt(3);
        v[i].z /= sqrt(3);
    }
    
    /*std::cout << "v[11] - " << v[11].x << "\n";
    std::cout << "v[12] - " << v[12].x << "\n";
    std::cout << "v[13] - " << v[13].x << "\n";
    std::cout << "v[14] - " << v[14].x << "\n";
    std::cout << "v[15] - " << v[15].x << "\n";
    std::cout << "v[16] - " << v[16].x << "\n";
    std::cout << "v[17] - " << v[17].x << "\n";
    std::cout << "v[18] - " << v[18].x << "\n";
    std::cout << "v[19] - " << v[19].x << "\n";*/

    f.triags[ 0] = make_triangle(v[4], v[0], v[6], color);
    f.triags[ 1] = make_triangle(v[0], v[5], v[6], color);
    f.triags[ 2] = make_triangle(v[0], v[4], v[1], color);
    f.triags[ 3] = make_triangle(v[0], v[3], v[7], color);
    f.triags[ 4] = make_triangle(v[2], v[0], v[7], color);
    f.triags[ 5] = make_triangle(v[0], v[1], v[3], color);
    
    f.triags[ 6] = make_triangle(v[10], v[1], v[11], color);
    f.triags[ 7] = make_triangle(v[3], v[1], v[10], color);
    f.triags[ 8] = make_triangle(v[1], v[4], v[11], color);
    f.triags[ 9] = make_triangle(v[5], v[0], v[8], color);
    f.triags[10] = make_triangle(v[0], v[2], v[9], color);
    f.triags[11] = make_triangle(v[8], v[0], v[9], color);
    
    f.triags[12] = make_triangle(v[5], v[8], v[16], color);
    f.triags[13] = make_triangle(v[6], v[5], v[12], color);
    f.triags[14] = make_triangle(v[12], v[5], v[16], color);
    f.triags[15] = make_triangle(v[4], v[12], v[15], color);
    f.triags[16] = make_triangle(v[4], v[6], v[12], color);
    f.triags[17] = make_triangle(v[11], v[4], v[15], color);
    
    f.triags[18] = make_triangle(v[2], v[13], v[17], color);
    f.triags[19] = make_triangle(v[2], v[7], v[13], color);
    f.triags[20] = make_triangle(v[9], v[2], v[17], color);
    f.triags[21] = make_triangle(v[13], v[3], v[14], color);
    f.triags[22] = make_triangle(v[7], v[3], v[13], color);
    f.triags[23] = make_triangle(v[3], v[10], v[14], color);
    
    f.triags[24] = make_triangle(v[8], v[17], v[19], color);
    f.triags[25] = make_triangle(v[16], v[8], v[19], color);
    f.triags[26] = make_triangle(v[8], v[9], v[17], color);
    f.triags[27] = make_triangle(v[14], v[11], v[18], color);
    f.triags[28] = make_triangle(v[11], v[15], v[18], color);
    f.triags[29] = make_triangle(v[10], v[11], v[14], color);
    
    f.triags[31] = make_triangle(v[12], v[19], v[18], color);
    f.triags[32] = make_triangle(v[15], v[12], v[18], color);
    f.triags[33] = make_triangle(v[12], v[16], v[19], color);
    f.triags[34] = make_triangle(v[19], v[13], v[18], color);
    f.triags[35] = make_triangle(v[17], v[13], v[19], color);
    f.triags[36] = make_triangle(v[13], v[14], v[18], color);

    //std::cout << "tr[46] - " << triags[46].a.x << "\n";
    //std::cout << "radius - " << Figure.radius << "\n";
    for (int i = 0; i < 37; i++) {
        f.triags[i].a = scale(f.triags[i].a, rad);
        f.triags[i].b = scale(f.triags[i].b, rad);
        f.triags[i].c = scale(f.triags[i].c, rad);
        
        //if(i == 12 || i == 13 || i == 14) std::cout << "trg.a.x * radius - " << triags[i].a.x << "\n";

        f.triags[i].a = add(f.triags[i].a, pos);
        f.triags[i].b = add(f.triags[i].b, pos);
        f.triags[i].c = add(f.triags[i].c, pos);
        
        //if(i == 12 || i == 13 || i == 14) std::cout << "trg.a.x + cntr - " << triags[i].a.x << "\n";
        
        //std::cout << triags[i].a.x << "\n";
    }

	return f;
}
