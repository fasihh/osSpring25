#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define RANGE 10000

typedef struct sort_args {
  int *arr;
  size_t l;
  size_t r;
} sort_args;

void merge(int *arr, size_t l, size_t m, size_t r) {
  int n1 = m - l + 1, n2 = r - m;
  int arr1[n1], arr2[n2];

  for (size_t i = 0; i < n1; ++i)
    arr1[i] = arr[l + i];
  for (size_t i = 0; i < n2; ++i)
    arr2[i] = arr[i + m + 1];

  size_t i = 0, j = 0, k = l;
  while (i < n1 && j < n2) {
    if (arr1[i] < arr2[j])
      arr[k++] = arr1[i++];
    else
      arr[k++] = arr2[j++];
  }

  while (i < n1)
    arr[k++] = arr1[i++];
  while (j < n2)
    arr[k++] = arr2[j++];
}

void *sort_th(void *args) {
  int *arr = ((sort_args *)args)->arr;
  size_t l = ((sort_args *)args)->l, r = ((sort_args *)args)->r;

  if (l >= r)
    pthread_exit(0);

  size_t m = l + (r - l) / 2;

  sort_args l_args = {arr, l, m}, r_args = {arr, m+1, r};
  pthread_t left, right;
  
  int th1 = pthread_create(&left, NULL, sort_th, (void *)&l_args);
  if (th1 != 0) {
    perror("thread creation failed");
    exit(1);
  }

  int th2 = pthread_create(&right, NULL, sort_th, (void *)&r_args);
  if (th2 != 0) {
    perror("thread creation failed");
    exit(1);
  }

  pthread_join(left, NULL);
  pthread_join(right, NULL);

  merge(arr, l, m, r);
  pthread_exit(0);
}

int main(int argc, char *argv[]) {
  srand(time(NULL));

  size_t n = argc >= 2 ? atoi(argv[1]) : 10000;
  int *arr = malloc(sizeof(int) * n);
  if (arr == NULL) {
    perror("malloc failed");
    exit(1);
  }

  for (size_t i = 0; i < n; ++i)
    arr[i] = rand() % RANGE;

  struct timeval start, end;
  gettimeofday(&start, NULL);
  
  sort_args args = {arr, 0, n - 1};
  pthread_t tid;
  int th = pthread_create(&tid, NULL, sort_th, (void *)&args);
  if (th != 0) {
    perror("thread creation failed");
    exit(1);
  }

  int thj = pthread_join(tid, NULL);
  if (thj != 0) {
    perror("join failed");
    exit(1);
  }
  
  gettimeofday(&end, NULL);

  long seconds = end.tv_sec - start.tv_sec;
  long microseconds = end.tv_usec - start.tv_usec;
  if (microseconds < 0) {
    seconds -= 1;
    microseconds += 1000000;
  }
  double elapsed = seconds + microseconds * 1e-6;

  printf("Elapsed time: %.6f seconds\n", elapsed);

  free(arr);
  return 0;
}