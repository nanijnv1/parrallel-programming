#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <omp.h>


int main()
{

float sum, *array, *prefixsum,store;
//printf("enter no. of numbers you to add " );
int size=10,i,ri,li,d,j,n;
//scanf("%d\n",&size );
array = ((float *) malloc(size * sizeof(float)));
prefixsum = ((float *) malloc((size+1) * sizeof(float)));
for(i=0;i<size;i++){
  array[i]=i*5;
}
for(i=0;i<size;i++){
  printf("%f\t",array[i] );
}
for(d=0;pow(2,d)<size;d++){
  #pragma omp parallel for{
  for(li=0;li<size;li=li+pow(2,d)){
    ri=li+pow(2,d);
    array[ri]=array[li]+array[ri];
  }
}
}
n=d;
store = array[size-1];
array[size-1]=0;
prefixsum=0;
for(i=n;pow(2,i)<size;i--){
 #pragma omp parallel for{
  for(li=d;li<size;li=li-pow(2,d)){
    li=pow(2,d);
    ri=li+pow(2,d);
    prefixsum[ri]=array[li]+prefixsum[ri];
  }
}
}
prefixsum[size+1]=store;
for(j = 1;j<size+1;j++) {
  printf("%f\t",prefixsum[j] );
}
printf("%f\t", prefixsum[size+1]);

printf("\n sum of numbers is %f \n",array[size-1]);
return 0;
}
