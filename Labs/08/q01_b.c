#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10000000
#define THREADS 10
#define SIZE_PER_THREAD (SIZE / THREADS)

float A[SIZE], B[SIZE], C[SIZE] = {0};

void init_array(float *arr, int n) {
  for (int i = 0; i < n; ++i)
    arr[i] = (float) (rand() % 1000) / 10;
}

void *runner(void *arg) {
  int start = (long)arg * SIZE_PER_THREAD;
  int end = start + SIZE_PER_THREAD;

  for (int i = start; i < end; ++i)
    C[i] += A[i] + B[i];

  return NULL;
}

int main() {
  srand(42);

  init_array(A, SIZE), init_array(B, SIZE);

  pthread_t workers[THREADS];
  for (int i = 0; i < THREADS; ++i) {
    printf("Start Sum (thread #%d)\n", i+1);
    workers[i] = pthread_create(&workers[i], NULL, runner, (void *)(long)i);
  }

  for (int i = 0; i < THREADS; ++i) {
    printf("End Sum (thread #%d)\n", i+1);
    pthread_join(workers[i], NULL);
  }

  printf("Writing initial 100 values\n");
  for (int i = 0; i < 100; ++i)
    printf("%.1f ", C[i]);
  printf("\n");

  return 0;
}