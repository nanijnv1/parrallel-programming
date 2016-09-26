#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int main()
{
	int  rows, cols, i, j;
	float **Mat, **Trans;


	printf("size of Mat \n");
	scanf("%d%d", &rows, &cols);

	if (rows <= 0 || cols <= 0) {
		printf("Therows And cols Should Be Of Positive Sign\n");
		exit(1);
	}

	Mat = (float **) malloc(sizeof(float) *rows);
	for (i = 0; i <rows; i++) {
		Mat[i] = (float *) malloc(sizeof(float) * cols);
		for (j = 0; j < cols; j++)
			Mat[i][j] = (i * j) * 5 + i;
	}

	Trans = (float **) malloc(sizeof(float) * cols);

	for (i = 0; i < cols; i++) {
		Trans[i] = (float *) malloc(sizeof(float) *rows);
		for (j = 0; j <rows; j++) {
			Trans[i][j] = 0.0;
		}
	}



#pragma omp parallel for private(j)
	for (i = 0; i <rows; i = i + 1)
		for (j = 0; j < cols; j = j + 1)
			Trans[j][i] = Mat[i][j];

	printf("The Input Mat Is \n");

	for (i = 0; i <rows; i++) {
		for (j = 0; j < cols; j++)
			printf("%f \t", Mat[i][j]);
		printf("\n");
	}

	printf("\nThe Transpose Mat Is \n");
	for (i = 0; i < cols; i = i + 1) {
		for (j = 0; j <rows; j = j + 1)
			printf("%f \t", Trans[i][j]);
		printf("\n");
	}


	free(Mat);
	free(Trans);
return 0;
}
