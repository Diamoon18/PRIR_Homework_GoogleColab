%%writefile saxpy_cpu.c
#include <stdio.h>
#include<stdlib.h>
#include<time.h>

void saxpy_cpu(int n, float a, float *x, float *y){
    for (int i = 0; i < n; i++) {
        y[i] = a * x[i] + y[i];
    }
}

int main(){
    
  int n = 1<<25;
  float *x, *y, alpha=2.0;
  x = (float*) malloc(n * sizeof(float));
  y = (float*) malloc(n * sizeof(float));

  clock_t start, stop; 
	for(int i = 1; i <= 50; i++){
			start=clock();
		
			saxpy_cpu(n, alpha, x, y);

			stop = clock(); 
			double d = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;                                                   
			printf("%lf\n", d);
	}	
  
  free(x);
  free(y);
}
