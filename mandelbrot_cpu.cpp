%%writefile mandelbrot_cpu.cpp
#include <math.h>
#include <chrono>
#include <iostream>
#include <sys/time.h>

using namespace std;

int computeMandelbrot(double X0, double Y0, double X1, double Y1, int POZ, int PION, int ITER,int *Mandel){
    double dX = (X1-X0)/(POZ-1);
    double dY = (Y1-Y0)/(PION-1);
    double x, y, Zx, Zy, tZx;
    int SUM;
    int i;
    for (int pion = 0; pion < PION; pion++){
        for (int poz = 0;poz < POZ; poz++){
            x = X0+poz*dX;
            y = Y0+pion*dY;
            Zx = x;
            Zy = y;
            i = 0;

            while( (i<ITER)  && ((Zx*Zx+Zy*Zy)<4))
            {
                tZx = Zx*Zx-Zy*Zy+x;
                Zy = 2*Zx*Zy+y;
                Zx = tZx;
                i++;
            }
            Mandel[pion*POZ+poz] = i;
            SUM+=i;
        }
    }
    return SUM;
}

int main(int argc, char **argv) {
    time_t start, end;
    
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
    
    int *Iters = (int*) malloc(sizeof(int)*POZ*PION);     
    unsigned int *RowSums  = (unsigned int*) malloc(sizeof(unsigned int)*PION);

    for(int i = 1; i <= 50; i++)
    {
        
        auto start2 = chrono::steady_clock::now();        
        int SUM = computeMandelbrot(X0,Y0,X1,Y1,POZ,PION,ITER,Iters);
        auto stop = chrono::steady_clock::now();      
        auto diff = stop - start2;
        cout << chrono::duration <double, milli> (diff).count() << endl;
        
    }
}
