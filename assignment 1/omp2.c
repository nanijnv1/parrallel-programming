#include<stdio.h>
#include <stdlib.h>
#include<omp.h>


int main()
{
	float *Array,sum;
	int size, i;

	printf("Enter the size of the array\n");
	scanf("%d", &size);

	if (size <= 0) {
		printf("Array Size Should Be Of Positive Value ");
		exit(1);
	}

	Array = (float *) malloc(sizeof(float) * size);
	for (i = 0; i < size; i++) {
		Array[i] = i * 5;
	}

	printf("The Array Elements Are \n");

	for (i = 0; i < size; i++)
		printf("%f\t", Array[i]);

	sum = 0.0;
#pragma omp parallel for shared(sum)
	for (i = 0; i < size; i++) {
#pragma omp critical
		sum = sum + Array[i];

	}
	free(Array);

	printf("\n sum of elements %f\n", sum);

}
