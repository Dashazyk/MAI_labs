#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include <stdint.h>

typedef unsigned long long int uint64_t;

#define PI_CNT 16
#define BL_CNT  16
#define PER_THREAD 64 / PI_CNT

#define CSC(call)                      \
do {                                \
    cudaError_t res = call;            \
    if (res != cudaSuccess) {        \
        fprintf(stderr, "ERROR in %s:%d. Message: %s\n",            \
            __FILE__, __LINE__, cudaGetErrorString(res));        \
        exit(0);                    \
    }                                \
} while(0)

__global__ void kernel(uint64_t number, uint64_t *ipowers, uint64_t *result, uint64_t *pokasa) {
    __shared__ uint64_t power_array[64]; 
    
    // вычисляется индекс элемента который будет обрабатываться
    int idx = threadIdx.x + blockIdx.x * blockDim.x; 

    //данный массив в начале заполняется степенями, которые были вычислены "по-быстрому"
    power_array[idx] = ipowers[idx / (64/PI_CNT)]; 

    //показатель степени, которая сейчас лежит в текущем эл-те массива
    int pokasatel_stepeni = pokasa[idx / (64/PI_CNT)]; 

    while (pokasatel_stepeni < idx) { //доводим степень до нужной
        power_array[idx] *= 2;
        pokasatel_stepeni++;
    }

    __syncthreads();

    result[idx] = power_array[idx];
}

int main(void) {
    uint64_t  initial_powers[PI_CNT];
    uint64_t *result = (uint64_t *)malloc(64 * sizeof(uint64_t));
    uint64_t  pokasa[PI_CNT];
    uint64_t step = pow(2, 64 / PI_CNT);
    uint64_t *ipowers_dev;
    uint64_t *result_dev;
    uint64_t *pokasa_dev; 
    uint64_t  number;

    cudaEvent_t before, after;
    CSC(cudaEventCreate(&before)); // инициализируем 2 события cuda
    CSC(cudaEventCreate(&after));

    printf("Enter the number: ");
    scanf ("%llu", &number);

    initial_powers[0] = 1;
    pokasa        [0] = 0;
    for (int i = 1; i < PI_CNT; ++i) {
        initial_powers[i] = initial_powers[i - 1] * step;
        pokasa        [i] = pokasa        [i - 1] + 64 / PI_CNT;
    }

    CSC(cudaMalloc(&ipowers_dev,                 PI_CNT * sizeof(uint64_t)));
    CSC(cudaMalloc(&pokasa_dev,                  PI_CNT * sizeof(uint64_t)));
    CSC(cudaMemcpy( ipowers_dev, initial_powers, PI_CNT * sizeof(uint64_t), cudaMemcpyHostToDevice));
    CSC(cudaMemcpy( pokasa_dev,  pokasa,         PI_CNT * sizeof(uint64_t), cudaMemcpyHostToDevice));

    CSC(cudaMalloc(&result_dev, 64 * sizeof(uint64_t)));

    CSC(cudaEventRecord(before)); // сохраняем текущее время начала работы ядра
    kernel<<<BL_CNT, 64 / BL_CNT>>>(number, ipowers_dev, result_dev, pokasa_dev);
    CSC(cudaGetLastError());
    CSC(cudaEventRecord(after)); // сохраняем время конца работы ядра

    CSC(cudaEventSynchronize(after));
    float t;
    CSC(cudaEventElapsedTime(&t, before, after)); // считаем время работы ядра
    CSC(cudaEventDestroy(before));
    CSC(cudaEventDestroy(after));
    printf("TIME = %g\n", t);

    CSC(cudaMemcpy(result, result_dev, 64 * sizeof(uint64_t), cudaMemcpyDeviceToHost));

    int tmp = -1;
    for (int i = 0; i < 64; ++i)
        if (result[i] == number)
            tmp = i;
    
    if (tmp > 0)
        printf("number %llu is %dth power of 2\n", number, tmp);
    else
        printf("Nope. it's no power of 2\n");

    return 0;
}