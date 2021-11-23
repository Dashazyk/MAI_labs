#include <iostream>
#include <cmath>
#include <vector>
#include <thrust/device_vector.h>
#include <thrust/sequence.h>
#include <thrust/sort.h>

// #define SIGN(x) ((x) > 0 ? 1 : ((x) ? -1 : 0))

#define CSC(call)  					\
	do {								\
		cudaError_t res = call;			\
		if (res != cudaSuccess) {		\
			fprintf(stderr, "ERROR in %s:%d. Message: %s\n",			\
					__FILE__, __LINE__, cudaGetErrorString(res));		\
			exit(0);					\
		}								\
	} while(0)

using namespace std;

#define co1 1.8
#define co2 2.8

__host__ __device__ double fun(double x) {
	return tan(co1 * x) - co2 * x;
}

__host__ __device__ double pi(void) {
	return M_PI / co1;
}

__device__ double bisection(double left, double right, double eps, int limit = 1000000) {
	double mid = 0;
	double fl  = fun(left);
	double fr  = fun(right);

	while (right - left > eps && abs(right - left) > abs(eps) && limit) {
		double fm;

		limit--;

		mid = (left + right) / 2;

		fm = fun(mid);
		// cout << left << "' '" << mid << " " << right << endl;
		// cout << fl   << "   " << fm  << " " << fr    << endl;
		// cout << endl;

		if (fm) {
			// если одинак знак с левого края и по середине
			if (fm * fl > 0) {
				fl   = fm;
				left = mid;
			}
			// если одинак знак с правого края и по середине
			if (fm * fr > 0) {
				fr    = fm;
				right = mid;
			}
		}
		else
			break;
	}

	return mid;
}

__global__ 
void caller(double *borders, double *results, double eps) {
	int idx = threadIdx.x + blockIdx.x * blockDim.x;

	results[idx] = bisection(borders[idx] + eps, borders[idx + 1] - eps, eps);
}

int main(void) {
	double left, right, eps;
	cout << "l, r, e: ";
	cin  >> left >> right >> eps;
	cudaEvent_t start, end;
	bool has_zero = false;

	if (eps > 0.0001)
		cout << "Epsilon is too big" << endl;

	// next, we kinda wanna to find all the tear points, don't we?
	double tear = floor(left / pi()) * pi() - pi() / 2;

	has_zero = left < 0 && right > 0;

	int size = (right + pi() - left) / pi() + 2;
	if (has_zero)
		size += 2;
		
	thrust::device_vector<double> tear_points(size);
	thrust::device_vector<double> results    (size - 1);

	thrust::sequence(tear_points.begin(), tear_points.end(), tear, pi());

	if (has_zero) {
		tear_points[size - 1] = 0 - 100 * eps;
		tear_points[size - 2] = 0 + 100 * eps;
		thrust::sort(tear_points.begin(), tear_points.end());
	}

	// we should add 0 as break point, otherwise there are 3 roots in there
	

	cout << "Size: "    << size << endl;
	cout << "Called the kernel" << endl;

	//~ for (int i = 0; i < tear_points.size(); ++i)
		//~ cout << tear_points[i] << endl;

	CSC(cudaEventCreate(&start));
	CSC(cudaEventCreate(&end  ));
	CSC(cudaEventRecord( start));
	caller<<<1, size - 1>>>(
		thrust::raw_pointer_cast(tear_points.data()),
		thrust::raw_pointer_cast(results.data()), 
		eps
	);
	CSC(cudaGetLastError());

	CSC(cudaEventRecord     (end));
	CSC(cudaEventSynchronize(end));
	float t;
	CSC(cudaEventElapsedTime(&t, start, end));
	CSC(cudaEventDestroy(start));
	CSC(cudaEventDestroy(end));		

	cout << "Results: " << endl;	
	for (int i = 1; i < results.size(); ++i) {
        double m = results[i];
        if (m > left && m < right) {
			cout << "Interval: [" << tear_points[i] << ", " << tear_points[i + 1] << "]" << endl;
			cout << "fun(" << m << ") = " << fun(m) << "\t (" << (int)fun(m) << ")" << endl;
			cout << endl;
		}
    }
    cout << "Time: " << t << endl;
	return 0;
}


