#include <stdio.h>
#include <stdint.h>
#include <time.h>

double get_ms() {
    struct timespec _t;
    clock_gettime(CLOCK_REALTIME, &_t);
    return _t.tv_sec*1000 + (_t.tv_nsec/1.0e6);
}

int main(void) {
    uint64_t number;
    uint64_t po2 = 1;

    scanf("%lu", &number);

    double start = get_ms();
    for (int power = 0; power < 64; ++power) {
        if (po2 == number) {
            printf("number %lu is %dth power of 2\n", number, power);
            break;
        }
        else if (po2 > number) {
            printf("Nope. it's no power of 2\n");
            break;
        }
        po2 *= 2;
    }
    double end = get_ms();

    printf("TIME = %g\n", end - start);

    return 0;
} 
