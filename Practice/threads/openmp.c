#include <stdio.h>
#include <omp.h>

int sum(int *arr, int n) {
  int total = 0;
  for (int i = 0; i < n; ++i)
    total += arr[i];
  return total;
}

int main() {
  int arr[] = {1, 2, 3, 4, 5};

  #pragma omp parallel
  {
    printf("sum 1: %d\n", sum(arr, sizeof(arr) / sizeof(int)));
  }

  printf("Hello World!\n");

  return 0;
}