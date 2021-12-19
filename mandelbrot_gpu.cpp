%%cu
#include <math.h>
#include <chrono>
#include <iostream>
#include <sys/time.h>

using namespace std;

__global__ void cudaMandelbrot(float X0, float Y0, float X1, float Y1, int POZ, int PION, int ITER,int *Mandel){
    double dX = (X1-X0)/(POZ-1);
    double dY = (Y1-Y0)/(PION-1);
    int i; 
    float x, y, Zx, Zy, tZx;

    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    int pion, poz;

      if (idx < PION*POZ) {  
            pion = idx / POZ;
            poz = idx % POZ;
            x = X0 + poz*dX;
            y = Y0 + pion*dY;
            Zx=x;
            Zy=y;
            i=0;

            while((i<ITER) && (Zx*Zx+Zy*Zy)<4) {
                tZx = Zx*Zx-Zy*Zy+x;
                Zy = 2*Zx*Zy+y;
                Zx=tZx;
                i++;
            }
            Mandel[idx] = i;     
      }	
}

int main(int argc, char **argv) {
    time_t start, end;
    cudaError_t status;

    //Zawężenie
    //obszar obliczeń {X0,Y0} - lewy dolny róg
    double X0=-0.82;    
    double Y0=0.1;

    //{X1,Y1} - prawy górny róg
    double X1=-0.7;   
    double Y1=0.22;

    //rozmiar w pikselach {POZ,PION} 
    int POZ=512; int PION=512;
    
    //liczba iteracji próbkowania {ITER}
    int ITER=256;

    //tablica do przechowywania wyniku na CPU i na GPU
    int* Mandel_device;
    status = cudaMalloc((void**)&Mandel_device, sizeof(int)*POZ*PION);

    int *Mandel_host = (int*) malloc(sizeof(int)*POZ*PION);
        
    // sprawdz czy alokacja się powiodła 
    if(status != cudaSuccess){
        cout << cudaGetErrorString(status) << endl;
    };

    dim3 threadsPerBlock(32,1,1);
    dim3 numBlocks(PION*POZ/threadsPerBlock.x+1,1,1);

    for(int i = 1; i <= 50; i++) {
        auto start2 = chrono::steady_clock::now();        
        cudaMandelbrot<<<numBlocks,threadsPerBlock,0>>>(X0, Y0, X1, Y1, POZ, PION, ITER, Mandel_device);
        
        status = cudaMemcpy(Mandel_host, Mandel_device, sizeof(int)*POZ*PION, cudaMemcpyDeviceToHost);
        if(status != cudaSuccess){
            cout << cudaGetErrorString(status) << endl;
        };
     
        auto stop = chrono::steady_clock::now();       
        auto diff = stop - start2;
        cout << chrono::duration <double, milli> (diff).count() << endl; 
    }
}
