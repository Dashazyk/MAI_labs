#include <stdlib.h>
#include <stdio.h> 
#include <math.h>
#include <iostream>
#include "Triangle.h"
#include "light.h"
#include "vect3.h"
#include "render.h"
#include "fig.h"

#ifndef GRID_SIZE
#define GRID_SIZE 16
#endif 

#ifndef BLOCK_SIZE
#define BLOCK_SIZE 16
#endif 

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define CSC(call)  													\
do {																\
	cudaError_t res = call;											\
	if (res != cudaSuccess) {										\
		fprintf(stderr, "ERROR in %s:%d. Message: %s\n",			\
				__FILE__, __LINE__, cudaGetErrorString(res));		\
		exit(0);													\
	}																\
} while(0)


struct cam {
    double r, z, phi;
    double Ar, Az;
    double omega_r, omega_z, omega_phi;
    double pr, pz;
};

using namespace std;

double get_ms() {
    struct timespec _t;
    clock_gettime(CLOCK_REALTIME, &_t);
    return _t.tv_sec*1000 + (_t.tv_nsec/1.0e6);
}

int main(int argc, char **argv) {
	int k, w, h;
	char buff[256];
	uchar4 *data;
	vect3 pc, pv;
	Light *lights;
	int fcnt = 5;
	int lcnt = 1;
	int tcnt = 0;
	Figure   *figs = (Figure *)malloc(sizeof(Figure) * fcnt);
	Light    *gpu_light;
	Triangle *gpu_triags;
	uchar4   *gpu_data;
	uchar4   *gpu_aata;
	int frames = 126;
	char output_name[256];
	double angle = 120.0;
	cam mc, mn;
	
	lights = (Light *)malloc(sizeof(Light) * lcnt);
	lights[0] = make_light({10, 1, 10}, 200);

	vect3  plane_color;
	vect3  plane_pos[4];

	bool is_gpu = true;
	bool is_sane = true;

	if (argc == 2 && !strcmp("--default", argv[1])) {
		printf("200");
		printf("800 600");
		printf("res/%%04d.data");
		printf("60");
		printf("8.0 3.0 0.0 2.0 1.0 2.0 6.0 1.0 0.0 0.0");
		printf("1.0 0.0 0.0 0.5 0.1 1.0 4.0 1.0 0.0 0.0");
		printf("-300  300 0");
		printf(" 300 -300 0");
		printf("-300 -300 0");
		printf(" 300  300 0");
		printf("1 0.9 0.9");
		printf( "1.0  1.0 1.0 0.5 0.0 0.5 0.3");
		printf("-1.0 -1.0 1.0 0.5 0.0 0.5 0.0");
		printf("1.0 -1.0 1.0 0.5 0.5 0.7 0.0");
		
		return 0;
	}
	else if (argc == 2 && !strcmp("--stb", argv[1]))
		is_sane = true;
	else if (argc == 2 && !strcmp("--cpu", argv[1]))
		is_gpu = false;
	
	vect3  dodec_color;
	vect3  dodec_pos;
	double dodec_rad;
	vect3  hexae_color;
	vect3  hexae_pos;
	double hexae_rad;
	vect3  icosa_color;
	vect3  icosa_pos;
	double icosa_rad;

	cin >> frames;
	cin >> w >> h;
	data = (uchar4*)malloc(sizeof(uchar4) * w * h);
	cin >> output_name;
	cin >> angle;

	cin >> mc.r >> mc.z >> mc.phi;
    cin >> mc.Ar >> mc.Az;
    cin >> mc.omega_r >> mc.omega_z >> mc.omega_phi;
    cin >> mc.pr >> mc.pz;
    
    cin >> mn.r >> mn.z >> mn.phi;
    cin >> mn.Ar >> mn.Az;
    cin >> mn.omega_r >> mn.omega_z >> mn.omega_phi;
    cin >> mn.pr >> mn.pz;
    
    cin >> plane_pos[0].x >> plane_pos[0].y >> plane_pos[0].z;
    cin >> plane_pos[1].x >> plane_pos[1].y >> plane_pos[1].z;
    cin >> plane_pos[2].x >> plane_pos[2].y >> plane_pos[2].z;
    cin >> plane_pos[3].x >> plane_pos[3].y >> plane_pos[3].z;
    cin >> plane_color.x >> plane_color.y >> plane_color.z;

	cin >> dodec_pos.x >> dodec_pos.y >> dodec_pos.z;
	cin >> dodec_rad;
	cin >> dodec_color.x >> dodec_color.y >> dodec_color.z;

	cin >> hexae_pos.x >> hexae_pos.y >> hexae_pos.z;
	cin >> hexae_rad;
	cin >> hexae_color.x >> hexae_color.y >> hexae_color.z;
	
	cin >> icosa_pos.x >> icosa_pos.y >> icosa_pos.z;
	cin >> icosa_rad;
	cin >> icosa_color.x >> icosa_color.y >> icosa_color.z;

	figs[0] = gen_floor(plane_color, plane_pos);
	figs[1] = gen_icosa(icosa_color, icosa_pos, icosa_rad);
	figs[2] = gen_hex  (hexae_color, hexae_pos, hexae_rad);
	figs[3] = gen_dodec(dodec_color, dodec_pos, dodec_rad);
	figs[4] = gen_dodec(dodec_color, {lights[0].pos.x, lights[0].pos.y, 0.15}, 0.3);

	for (int i = 0; i < fcnt; ++i)
		tcnt += figs[i].triag_count;

	printf("sane output: %d\n", is_sane);
	if (is_gpu) {
		CSC(cudaMalloc(&gpu_triags, sizeof(Triangle) * tcnt));
		CSC(cudaMalloc(&gpu_light,  sizeof(Light)    * lcnt));
		CSC(cudaMalloc(&gpu_data,   sizeof(uchar4)   * w * h));
		CSC(cudaMalloc(&gpu_aata,   sizeof(uchar4)   * w * h));

		CSC(cudaMemcpy(gpu_light, lights, sizeof(Light) * lcnt, cudaMemcpyHostToDevice));

		int tmp = 0;
		for (int i = 0; i < fcnt; ++i) {
			CSC(cudaMemcpy(gpu_triags + tmp, figs[i].triags, sizeof(Triangle) * figs[i].triag_count, cudaMemcpyHostToDevice));
			tmp += figs[i].triag_count;
		}
	}

	for (k = 0; k < frames; k++) {
		double t = 2 * M_PI * k / frames;
        
        pc = (vect3) {
            mc.r + mc.Ar * sin(mc.omega_r * t + mc.pr),
            mc.z + mc.Az * sin(mc.omega_z * t + mc.pz),
            mc.phi + mc.omega_phi * t
        };
        
        pv = (vect3) {
            mn.r + mn.Ar * sin(mn.omega_r * t + mn.pr),
            mn.z + mn.Az * sin(mn.omega_z * t + mn.pz),
            mn.phi + mn.omega_phi * t
        };
        
        pc = (vect3) {pc.x * cos(pc.z), pc.x * sin(pc.z), pc.y};
        pv = (vect3) {pv.x * cos(pv.z), pv.x * sin(pv.z), pv.y};

		if (is_gpu) {
			raytrace<<<dim3(GRID_SIZE, GRID_SIZE), dim3(BLOCK_SIZE, BLOCK_SIZE)>>> (
				gpu_triags, tcnt,
				gpu_light,  lcnt,
				{0.15, 0.15, 0.15}, // ambient
				pc, pv,
				w, h, angle,
				gpu_data
			);
			CSC(cudaGetLastError ());
			antiaaliasing<<<dim3(GRID_SIZE, GRID_SIZE), dim3(BLOCK_SIZE, BLOCK_SIZE)>>> (gpu_data, gpu_aata, w, h, 1);
			CSC(cudaGetLastError ());
			
			CSC(cudaMemcpy(data, gpu_aata, sizeof(uchar4) * w * h, cudaMemcpyDeviceToHost));
		}
		else {
			//~ Triangle *triags = (Triangle *)malloc(sizeof(Triangle) * tcnt);
			//~ tmp = 0;
			//~ memcpy(triags + tmp, floor.triags, sizeof(Triangle) * floor.triag_count);
			//~ tmp += floor.triag_count;
			//~ memcpy(triags + tmp, icosa.triags, sizeof(Triangle) * icosa.triag_count);
			//~ tmp += icosa.triag_count;
			//~ memcpy(triags + tmp, hexae.triags, sizeof(Triangle) * hexae.triag_count);
			//~ tmp += hexae.triag_count;
			//~ memcpy(triags + tmp, dodec.triags, sizeof(Triangle) * dodec.triag_count);
			//~ tmp += dodec.triag_count;

			//~ cpu(triags, tmp, lights[0], pc, pv, w, h, angle, data);
		}


		printf("%04d ", k);
		fflush(stdout);
		if (is_sane) {
			// based on convinient uchar4 layout in memory
			sprintf(buff, "res/%04d.jpg", k);
			printf("%s\n", buff);
			stbi_write_jpg(buff, w, h, 4, data, 100);
		}
		else {
			sprintf(buff, output_name, k);

			FILE *out = fopen(buff, "wb");
			fwrite(&w, sizeof(int), 1, out);
			fwrite(&h, sizeof(int), 1, out);	
			fwrite(data, sizeof(uchar4), w * h, out);
			fclose(out);
		}
	}
	printf("\n");
	free(data);	
	return 0;
}
