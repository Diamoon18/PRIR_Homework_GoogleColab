%%cu
#include <stdio.h>
#include<stdlib.h>
#include<time.h>

__global__ void saxpy_cuda(int n, float a, float *x, float *y){
    int tid = threadIdx.x + blockDim.x * blockIdx.x;
    int stride = blockDim.x * gridDim.x;
    for (int i = tid; i < n; i += stride) {
        y[i] = a * x[i] + y[i];
    }
}

int main(){
    int n = 1<<25;
    float *x, *y, alpha=2.0;

    cudaMalloc(&x, n * sizeof(float));
    cudaMalloc(&y, n * sizeof(float));

    clock_t start, stop; 
	  for(int i = 1; i <= 50; i++){
        start=clock();
      
        saxpy_cuda<<<32, 1024>>>(n, alpha, x, y);
        cudaDeviceSynchronize();

        stop = clock(); 
        double d = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;                                                   
        printf("%lf\n", d);
    }	
    
    cudaFree(x);
    cudaFree(y);
}
