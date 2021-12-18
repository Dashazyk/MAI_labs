#include <omp.h>
#include "render.h"

struct ray_intersection {
	double dst_min;
	int index;
	vect3 intersection;
};

__host__ __device__ ray_intersection ray(Triangle *triags, int trig_cnt, vect3 pos, vect3 dir) {
	int k, k_min = -1;
	double ts_min = 100;

	dir = norm(dir);

	ray_intersection result;
	
	for (k = 0; k < trig_cnt; k++) {
		vect3 side1 = diff(triags[k].b, triags[k].a); 
		vect3 side2 = diff(triags[k].c, triags[k].a); 
		vect3 p = prod(dir, side2); 
		
		double div = dot(p, side1);
		if (fabs(div) >= 1e-10) {
			vect3 t = diff(pos, triags[k].a);
			double u = dot(p, t) / div;
			if (!(u < 0.0 || u > 1.0)) {
				vect3  q = prod(t, side1);
				double v = dot(q, dir) / div;
				
				if (!(v < 0.0 || v + u > 1.0)) {
					double ts = dot(q, side2) / div;
					if (ts >= 0.0) {
						if (k_min == -1 || ts < ts_min) {
							k_min = k;
							ts_min = ts;
						}
					}
				}
			}
		}
	}

	result.index = k_min;
	if (k_min != -1) {
		result.dst_min   = ts_min;
		result.intersection = add(pos, scale(dir, ts_min));
	}
	
	return result;
}

__host__ __device__ __host__ int lin_index(int x, int y, int w, int h) {
	return (h - 1 - y) * w + x;
}

__global__ void antiaaliasing(uchar4 *data, uchar4 *odata, int w, int h, int r) {
	int idx     = blockDim.x * blockIdx.x + threadIdx.x;
	int idy     = blockDim.y * blockIdx.y + threadIdx.y;
	int offsetx = blockDim.x * gridDim.x;
	int offsety = blockDim.y * gridDim.y;

	//~ int r = 2;
	for (int x = idx; x < w; x += offsetx)
		for (int y = idy; y < h; y += offsety) {
			int vx = 0, vy = 0, vz = 0;

			for (int dx = -r; dx <= r; dx++)
				for (int dy = -r; dy <= r; dy++) {
					int fx = x + dx;
					int fy = y + dy;

					if (fx >= 0 && fx < w && fy >= 0 && fy < h) {
						vx += data[lin_index(fx, fy, w, h)].x;
						vy += data[lin_index(fx, fy, w, h)].y;
						vz += data[lin_index(fx, fy, w, h)].z;
					}
				}
			odata[lin_index(x, y, w, h)].x = vx / ((r+1) * (r+1) * 4.0);
			odata[lin_index(x, y, w, h)].y = vy / ((r+1) * (r+1) * 4.0);
			odata[lin_index(x, y, w, h)].z = vz / ((r+1) * (r+1) * 4.0);
			//~ data[lin_index(x, y, w, h)].x /= 2;
			//~ data[lin_index(x, y, w, h)].y /= 2;
			//~ data[lin_index(x, y, w, h)].z /= 2;
		}
}


__host__ __device__ vect3 calc_light(
	Triangle *triags,
	int trig_cnt,
	ray_intersection pseen,
	Light light,
	vect3 pc
) {
	vect3 dir_lit = norm(diff(pseen.intersection, light.pos));
	ray_intersection plit;
	double sc = 0;
	vect3 col_sc = {sc, sc, sc};

	plit = ray(triags, trig_cnt, light.pos, dir_lit);

	/*
	if (plit.index == pseen.index) {
		double light_distance = plit.dst_min / light.intensity;
		
		if (light_distance < 1)
			light_distance = 1;
		sc = dot(triags[pseen.index].normal, dir_lit) / light_distance;
		
		sc = abs(sc);

		col_sc.x = light.col.x * sc;
		col_sc.y = light.col.y * sc;
		col_sc.z = light.col.z * sc;

		col_sc.x = (1 - ambient) * col_sc.x + ambient;
		col_sc.y = (1 - ambient) * col_sc.y + ambient;
		col_sc.z = (1 - ambient) * col_sc.z + ambient;
	}
	*/
	if (plit.index == pseen.index) {
		double distance_fade = (light.intensity - plit.dst_min) / light.intensity;
		if (distance_fade > 0) {
			sc = distance_fade * dot(triags[pseen.index].normal, dir_lit);
			
			sc = abs(sc);

			col_sc.x = light.col.x * sc;
			col_sc.y = light.col.y * sc;
			col_sc.z = light.col.z * sc;

			vect3 dir2lit = norm(diff(light.pos, pseen.intersection));
			vect3 dir2cam = norm(diff(pc,        pseen.intersection));
			
			double a_fall = dot(triags[pseen.index].normal, dir2lit);
			double a_refl = dot(triags[pseen.index].normal, dir2cam);
			double a_diff = abs(a_fall - a_refl);

			vect3 n1 = prod( prod(triags[pseen.index].normal, dir2lit), dir2cam);
			//~ vect3 n2 = norm(prod(triags[pseen.index].normal, dir2cam));
			double l_diff = length(n1);

			//~ double full_reflcoef = distance_fade * pow( (1 - l_diff) * (1 - a_diff), 2 );
			//~ if (l_diff * a_diff < 0.0001) 
			//~ col_sc = add(col_sc, scale(light.col, full_reflcoef));
			
		}
	}
	
	return col_sc;
}

__host__ __device__ uchar4 raytrace_color(
	Triangle *triags, int trig_cnt,
	Light *light, int light_cnt,
	vect3 ambient,
	vect3 pc, vect3 dir_seen
) {
	uchar4 col = {0, 0, 0, 0};
	ray_intersection pseen = ray(triags, trig_cnt, pc, dir_seen);
	
	if (pseen.index >= 0) {
		vect3 sum_sc = {0, 0, 0};

		for (int lind = 0; lind < light_cnt; ++lind) {
			//~ sum_sc += calc_light(triags, trig_cnt, pseen, light[lnum]);
			sum_sc = add(
				sum_sc,
				calc_light(triags, trig_cnt, pseen, light[lind], pc)
			);

			//~ vect3 dir_lit = norm(diff(pseen.intersection, light[lind].pos));
			//~ double a_fall = dot(dir_lit,  triags[pseen.index].normal);
			//~ double a_refl = dot(dir_seen, triags[pseen.index].normal);

			//~ if (abs(abs(a_fall) - abs(a_refl)) < 0.1)
				//~ sum_sc = add(sum_sc, {1.0, 1.0, 1.0});
		}

		sum_sc.x = MIN(sum_sc.x, 1.0);
		sum_sc.y = MIN(sum_sc.y, 1.0);
		sum_sc.z = MIN(sum_sc.z, 1.0);
		
		//~ sum_sc = v2limits(sum_sc, ambient, {0.8, 0.8, 0.8});
		sum_sc = v2limits(sum_sc, ambient, {1, 1, 1});
		
		col.x = sum_sc.x * triags[pseen.index].color.x;
		col.y = sum_sc.y * triags[pseen.index].color.y;
		col.z = sum_sc.z * triags[pseen.index].color.z;
	}

#ifdef DEBUG
	for (int lind = 0; lind < light_cnt; ++lind) {
		vect3 lightvect = diff(light[lind].pos, pc);
		double lightcos = abs(dot(dir_seen, norm(lightvect)));
		if (lightcos > 0.99) {
			col.x = light[lind].col.x * 255;
			col.y = light[lind].col.y * 255;
			col.z = light[lind].col.z * 255;
			break;
		}
	}
#endif
	return col;
}

__global__ void raytrace(
	Triangle *triags, int trig_cnt,
	Light *light, int light_cnt,
	vect3 ambient,
	vect3 pc, vect3 pv,
	int w, int h,
	double angle, uchar4 *data
) {
	int idx     = blockDim.x * blockIdx.x + threadIdx.x;
	int idy     = blockDim.y * blockIdx.y + threadIdx.y;
	int offsetx = blockDim.x * gridDim.x;
	int offsety = blockDim.y * gridDim.y;
	
	double dw = 2.0 / (w - 1.0);
	double dh = 2.0 / (h - 1.0);
	double z  = 1.0 / tan(angle * M_PI / 360.0);
	
	vect3 bz = norm(diff(pv, pc));
	vect3 bx = norm(prod(bz, {0.0, 0.0, 1.0}));
	vect3 by = norm(prod(bx, bz));
	
	for (int x = idx; x < w; x += offsetx)	
		for (int y = idy; y < h; y += offsety) {
			double tx = -1.0 + dw * x;
			double ty = -1.0 + dh * y;
			
			vect3 v = {
				tx, 
				ty * h / w, 
				z
			}; 
			vect3 dir_seen = norm(mult(bx, by, bz, v)); 
			data[lin_index(x, y, w, h)] = raytrace_color(triags, trig_cnt, light, light_cnt, ambient, pc, dir_seen);
		}
}


void cpu(
	Triangle *triags, int trig_cnt,
	Light *light, int light_cnt,
	vect3 ambient,
	vect3 pc, vect3 pv,
	int w, int h,
	double angle, uchar4 *data
) {

	double dw = 2.0 / (w - 1.0);
	double dh = 2.0 / (h - 1.0);
	double z  = 1.0 / tan(angle * M_PI / 360.0);
	
	vect3 bz = norm(diff(pv, pc));
	vect3 bx = norm(prod(bz, {0.0, 0.0, 1.0}));
	vect3 by = norm(prod(bx, bz));
	
	int x, y;
	#pragma omp parallel for private(x, y) shared(data, bx, by, bz, triags, trig_cnt, pc, light, light_cnt, ambient)
	for (x = 0; x < w; x += 1)	
		for (y = 0; y < h; y += 1) {
			double tx = -1.0 + dw * x;
			double ty = -1.0 + dh * y;
			
			vect3 v = {
				tx, 
				ty * h / w, 
				z
			}; 
			vect3 dir_seen = norm(mult(bx, by, bz, v)); 
			data[lin_index(x, y, w, h)] = raytrace_color(triags, trig_cnt, light, light_cnt, ambient, pc, dir_seen);
		}
}
