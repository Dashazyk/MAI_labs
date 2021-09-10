#include <stdio.h>
#include <stdlib.h>

#define CSC(call)                      \
do {                                \
    cudaError_t res = call;            \
    if (res != cudaSuccess) {        \
        fprintf(stderr, "ERROR in %s:%d. Message: %s\n",            \
                __FILE__, __LINE__, cudaGetErrorString(res));        \
        exit(0);                    \
    }                                \
} while(0)

__global__ void kernel(int *arr1, int n) { //global значит ф-ию можно вызвать из хоста, несмотря на то что выполняться она будет на девайсе
    int idx = threadIdx.x + blockIdx.x * blockDim.x; //магия связанная с кол-м тредов и распределением чиселок по ним
    int offset = blockDim.x * gridDim.x;//на сколько раз перемещаемся в каждом из шагов вцикле
    
    while(idx < n/2) {
		int tmp = arr1[idx];
        arr1[idx] = arr1[n - idx - 1];
        arr1[n - idx - 1] = tmp;
        idx += offset;
    }
}

__global__ void kernelByt(int *arr1, int n) { //global значит ф-ию можно вызвать из хоста, несмотря на то что выполняться она будет на девайсе
    int idx = threadIdx.x + blockIdx.x * blockDim.x; //магия связанная с кол-м тредов и распределением чиселок по ним
    int offset = blockDim.x * gridDim.x;//на сколько раз перемещаемся в каждом из шагов вцикле
    
    while(idx < n) {
		arr1[idx] = ~arr1[idx];
        idx += offset;
    }
}


int main(){
	int *arrHost = (int *)malloc(512*sizeof(int));
	int *arrDev;
	int i;
	
	for (i = 0; i < 512; i++)
		arrHost[i] = i + 1;
	
    cudaEvent_t before, after;
    CSC(cudaEventCreate(&before));
    CSC(cudaEventCreate(&after));

	CSC(cudaMalloc(&arrDev, 512*sizeof(int)));
	CSC(cudaMemcpy(arrDev, arrHost, 512*sizeof(int), cudaMemcpyHostToDevice));
	
    CSC(cudaEventRecord(before));
	//~ kernelByt<<<256, 256>>>(arrDev, 512);  //кол-во threadов
	kernel<<<256, 256>>>(arrDev, 512);
	
    CSC(cudaGetLastError());
    CSC(cudaEventRecord(after));

    CSC(cudaEventSynchronize(after));
    float t;
    CSC(cudaEventElapsedTime(&t, before, after));
    CSC(cudaEventDestroy(before));
    CSC(cudaEventDestroy(after));

    printf("time = %f\n", t); //выводим посчитанную разницу во времени
    
    CSC(cudaMemcpy(arrHost, arrDev, 512*sizeof(int), cudaMemcpyDeviceToHost));
    
    for (i = 0; i < 512; i++){
		printf("%d ", arrHost[i]);
	}	
	printf("\n");
	CSC(cudaFree(arrDev));
	free(arrHost);
	return 0;
}
