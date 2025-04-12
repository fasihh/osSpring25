#include <stdio.h>
#include <stdlib.h>

#define SIZE 10000000

float A[SIZE], B[SIZE], C[SIZE] = {0};

void init_array(float *arr, int n) {
  for (int i = 0; i < n; ++i)
    arr[i] = (float) (rand() % 1000) / 10;
}

int main() {
  srand(42);

  init_array(A, SIZE), init_array(B, SIZE);

  printf("Performing Sum\n");
  for (int i = 0; i < SIZE; ++i)
    C[i] += A[i] + B[i];
  printf("Sum completed\n");

  printf("Writing initial 100 values\n");
  for (int i = 0; i < 100; ++i)
    printf("%.1f ", C[i]);
  printf("\n");

  return 0;
}