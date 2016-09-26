#include <stdio.h>

  void print_matrix(int n, int m[n][n]); 
  void print_vector(int n, int v[n]); 
  void matrix_x_vector(int n, int y[n], int x[n][n], int A[n]); 

int main()
{
  // Define Variables
  int n = 4;
  int m1[4] = {1, 2, 3, 4};
  int m2[4][4] = {
    {1,2,3,4},
    {5,6,7,8},
    {9,10,11,12},
    {13,14,15,16}
  };
  
  int multiplied_matrix[4] = {0,0,0,0};

  print_vector(n, m1);
  print_matrix(n, m2);
  matrix_x_vector(n, m1, m2, multiplied_matrix);
  printf("\n");
}

void print_matrix(int n, int m[n][n])
{
  int i, j; // i = row; j = column;
  printf("\nMatrix Given\n");
  for (i=0; i<n; i++)
  {
    for (j=0; j<n; j++)
      printf("%3i", m[i][j]);
    printf("\n");
  }
}

void print_vector(int n, int v[n])
{
  int i;
  printf("\nVector Given\n");
  for (i=0; i<n; i++)
    printf("%3i", v[i]);
  printf("\n");
}


void matrix_x_vector(int n, int y[n], int x[n][n], int A[n])
{
  int i, j,tid,no_threads,temp=0; // i = row; j = column;
  printf("\nResulted Matrix of [M]*[V]\n");
  
  omp_set_nested(1); 
  #pragma omp parallel private(i,j,tid) firstprivate(temp) shared(no_threads)
  {
  
  tid = omp_get_thread_num(); 
  no_threads = omp_get_num_threads();
  for (i=tid; i<n; i = i+no_threads)
  {

    #pragma omp parallel for reduction(+:temp)
    for (j=0; j<n; j++)
      temp += x[i][j] * y[j];

     A[i] = temp;
     temp=0;
  }
}
  
  for (i=0; i<n; i++)
    printf("%4i\n", A[i]);
}
