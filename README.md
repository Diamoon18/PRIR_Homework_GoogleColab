# PRIR_Homework_GoogleColab
## 1. Negative picture Lenna512x512 in CPU and GPU

## 2. SAXPY in CPU and GPU (from "Karty graficzne")
### What is it SAXPY?
SAXPY stands for “Single-Precision A·X Plus Y”. \
It is a function in the standard Basic Linear Algebra Subroutines (BLAS)library.\
SAXPY is a combination of scalar multiplication and vector addition, and it’s very simple:\
```it takes as input two vectors of 32-bit floats X and Y with N elements each, and a scalar value A``` \
It multiplies each element X[i] by A and adds the result to Y[i].\
### Results
I did 50 iterations to compare the runtime.\
We do large SAXPY calculations (n =~ 33554432245.997000)
We can see the differences in the execution time of the programs right away.
#### SAXPY CPU results
![image](https://user-images.githubusercontent.com/72127610/146678934-b2d0e058-a39d-4bcd-982b-8536a40efeb0.png)
#### SAXPY GPU results
![image](https://user-images.githubusercontent.com/72127610/146678952-73be4fbd-d05f-4f9e-a1d4-9121b18aac88.png)
#### Compare chart
Blue - time in s CPU\
Orange - time in s GPU\
From this chart I can make a conclusion that the GPU code version ```is more efficient``` than the CPU.\
Acceleration relative to the CPU = 33,79834437\
Also, the time in the CPU are jumping (line curve), while the GPU keeps the same time with a small difference (line straight)
![image](https://user-images.githubusercontent.com/72127610/146680766-beca18a7-4caf-466f-8353-168a59474a1e.png)

