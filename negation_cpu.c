%%writefile negation.c

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void negation(char* filename){
	FILE* fp = fopen(filename, "rb");

	unsigned char *imageData; 
	unsigned char *newimageData; 
	unsigned char imageHeader[54]; 
	unsigned char colorTable[1024];

	int i,j;

	fread(imageHeader, sizeof(unsigned char), 54, fp);

	int width = *(int*)&imageHeader[18];
	int height = *(int*)&imageHeader[22];
	int bitDepth = *(int*)&imageHeader[28];

	int imgDataSize = width * height; 

	imageData = (unsigned char*)malloc (imgDataSize * sizeof(unsigned char));
	newimageData = (unsigned char*)malloc (imgDataSize * sizeof(unsigned char));

	if(bitDepth <= 8)	
		fread(colorTable, sizeof(unsigned char), 1024, fp);


	fread(imageData, sizeof(unsigned char), imgDataSize, fp);

	for(i = 0; i < height; i++){
		for(j = 0; j < width; j++){                   
			newimageData[i*width + j] = 255 - imageData[i*width + j]; 
		}   
	}

	char* newFilename = "negation_res.bmp";
	FILE *fo = fopen(newFilename, "wb");

	fwrite(imageHeader, sizeof(unsigned char), 54, fo);

	if(bitDepth <= 8)
		fwrite(colorTable, sizeof(unsigned char), 1024, fo);

	fwrite(newimageData, sizeof(unsigned char), imgDataSize, fo); 

	fclose(fo);
	fclose(fp);
}

int main()
{
	clock_t start, stop; 
	for(int i = 1; i <= 50; i++){
		start=clock();
		
		negation("testLenna.bmp");

		stop = clock(); 
		double d = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;                                                   
		printf("%lf\n", i, d);
	}	
}
