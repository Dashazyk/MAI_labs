#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
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

typedef struct {
	int w, h;
	uchar4 *data;
} image;


// текстурная ссылка <тип элементов, размерность, режим нормализации>
texture<uchar4, 2, cudaReadModeElementType> tex;

__global__ void kernel(
	uchar4 *out, int w, int h, 
	float *fmatrix, int msize
) {
	int idx     = blockDim.x * blockIdx.x + threadIdx.x;
	int idy     = blockDim.y * blockIdx.y + threadIdx.y;
	int offsetx = blockDim.x * gridDim.x;
	int offsety = blockDim.y * gridDim.y;
	int x, y;

	for (y = idy; y < h; y += offsety)
		for (x = idx; x < w; x += offsetx) {
			// uchar4 newcol;
			uchar4 p;

			// p  = tex2D(tex, x, y);
			
			// newcol.x = p.x * 0.15;
			// newcol.y = p.y * 0.7;
			// newcol.z = p.z * 0.15;
			
			// out[y * w + x] = newcol;

			int lx, ly;
			int mcenter = msize / 2;
			double col[] = {0, 0, 0};
			for (lx = 0; lx < msize; ++lx)
				for (ly = 0; ly < msize; ++ly) {
					p = tex2D(tex, x + lx - mcenter, y + ly - mcenter);
					col[0] += (int)p.x * fmatrix[ly * msize + lx];
					col[1] += (int)p.y * fmatrix[ly * msize + lx];
					col[2] += (int)p.z * fmatrix[ly * msize + lx];
				}

			for (int i = 0; i < 3; ++i)
				//col[i] /= 2;
				if (col[i] > 255)
					col[i] = 255;

			out[y * w + x] = make_uchar4(col[0], col[1], col[2], 0);
		}
}

image img_read(char *fname) {
	unsigned char *tdata;
	image img;
	int t;

	fprintf(stderr, "loading image %s\n", fname);
	tdata = stbi_load(fname, &img.w, &img.h, &t, 4);
	fprintf(stderr, "size: %dx%d\n", img.w, img.h);

	img.data = (uchar4 *)malloc(sizeof(uchar4) * img.w * img.h);
	memcpy(img.data, tdata, sizeof(uchar4) * img.w * img.h);

	free(tdata);
	fprintf(stderr, "finished loading\n");

	return img;
}


int img_write(char *fname, image img) {
	int err = 0;
	
	// if (str_ends_with(fname, ".jpg"))
	fprintf(stderr, "Writing data to %s\n", fname);
	// printf("%d%d%d\n", img.data[0].x, img.data[0].y, img.data[0].z);
	stbi_write_jpg(fname, img.w, img.h, 4, img.data, 100);
	// stbi_write_bmp(fname, img.w, img.h, 4, img.data);

	return err;
}

int main(int argc, char **argv) {
	int     err = 0;
	char   *inm = NULL;
	char   *onm = NULL;
	char    t1[100];
	char    t2[100];
	// uchar4 *data;
	cudaEvent_t start, end;
	image input;

	if (argc == 1) {
		scanf("%s", t1); 
		scanf("%s", t2);
			
		inm = t1;
		onm = t2;
	}
	else {
		inm = argv[1];
		onm = argv[2];
	}

	if (!err) {
		// finp = fopen(inm, "rb");
		// fout = fopen(onm, "wb");
		
		fprintf(stderr, "inname: %s\n", inm);
		fprintf(stderr, "otname: %s\n", onm);
	}
	
	input = img_read(inm);
	
	fprintf(stderr, "%dx%d\n", input.w, input.h);
	
	// data = (uchar4 *)malloc(sizeof(uchar4) * input.w * input.h);
	
	if (input.data) {
		cudaArray *arr;
		
		// fprintf(stderr, "Reading data\n");
		// fread(data, sizeof(uchar4), w * h, finp);

		// fprintf(stderr, "Reading ok\n");

		// Подготовка данных для текстуры
		cudaChannelFormatDesc ch = cudaCreateChannelDesc<uchar4>();
		CSC(cudaMallocArray(&arr, &ch, input.w, input.h));
		
		if (arr) {
			float  *hst_fmatrix;
			float  *dev_fmatrix;
			int     fmsize;

			scanf("%d", &fmsize);
			hst_fmatrix = (float *)malloc(sizeof(float) * fmsize * fmsize);
			for (int i = 0; i < fmsize * fmsize; ++i)
				scanf("%g", hst_fmatrix + i);
			CSC(cudaMalloc(&dev_fmatrix, fmsize * fmsize * sizeof(float)));
			CSC(cudaMemcpy( dev_fmatrix, hst_fmatrix, sizeof(float) * fmsize * fmsize, cudaMemcpyHostToDevice));
				
			uchar4 *dev_out;
				
			CSC(cudaMemcpyToArray(arr, 0, 0, input.data, sizeof(uchar4) * input.w * input.h, cudaMemcpyHostToDevice));

			// Подготовка текстурной ссылки, настройка интерфейса работы с данными
			tex.addressMode[0] = cudaAddressModeClamp;	// Политика обработки выхода за границы по каждому измерению
			tex.addressMode[1] = cudaAddressModeClamp;
			tex.channelDesc = ch;
			//tex.filterMode  = cudaFilterModePoint; // original 
			//tex.normalized  = false;
			tex.filterMode  = cudaFilterModePoint;
			tex.normalized  = false;

			// Связываем интерфейс с данными
			CSC(cudaBindTextureToArray(tex, arr, ch));

			CSC(cudaMalloc(&dev_out, sizeof(uchar4) * input.w * input.h));

			fprintf(stderr, "Launching kernel\n");
			CSC(cudaEventCreate(&start));
			CSC(cudaEventCreate(&end  ));
			CSC(cudaEventRecord( start));
			//~ fprintf(stderr, "Launching kernel\n");
			//kernel<<<dim3(GRID_SIZE, GRID_SIZE), dim3(BLOCK_SIZE, BLOCK_SIZE)>>>(dev_out, w, h, dev_fmatrix, fmsize);
			int gridsize = 16;
			int blocksize = 32;
			
			kernel<<<dim3(gridsize, gridsize), dim3(blocksize, blocksize)>>>(dev_out, input.w, input.h, dev_fmatrix, fmsize);
			
			CSC(cudaGetLastError());
			CSC(cudaEventRecord     (end));
			CSC(cudaEventSynchronize(end));
			float t;
			CSC(cudaEventElapsedTime(&t, start, end));
			CSC(cudaEventDestroy(start));
			CSC(cudaEventDestroy(end));
			fprintf(stderr, "Finished kernel\n");

			fprintf(stderr, "time = %f\n", t);
			//~ fprintf(stderr, "Kernel finished\n");

			CSC(cudaMemcpy(input.data, dev_out, sizeof(uchar4) * input.w * input.h, cudaMemcpyDeviceToHost));
			fprintf(stderr, "Copying back finished\n");

			// Отвязываем данные от текстурной ссылки
			CSC(cudaUnbindTexture(tex));
			fprintf(stderr, "Unbind finished\n");

			//~ CSC(cudaFreeArray(arr));
			//~ CSC(cudaFree(dev_out));
		}
		else
			err = 97;
	}
	else
		err = 96;

	// fclose(finp);
	
	// if (fout) {
	// fprintf(stderr, "Writing data\n");

	// fwrite(&w,   sizeof(int), 1, fout);
	// fwrite(&h,   sizeof(int), 1, fout);
	// fwrite(data, sizeof(uchar4), w * h, fout);
	
	// fclose(fout);
	//~ free  (data);
	img_write(onm, input);
	
	// fprintf(stderr, "Data written\n");
	// }
	// else
	// 	err = 98;
		
	if (err)
		fprintf(stderr, "E: error with code %d has occured!\n", err);
	
	return err;
}
