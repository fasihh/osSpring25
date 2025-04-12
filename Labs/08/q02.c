#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

int n;
int mean_val = 0;
int max_val = INT_MIN;
int min_val = INT_MAX;

void *mean(void *args) {
  for (int i = 0; i < n; ++i)
    mean_val += *((int *)args + i);
  mean_val /= n;

  pthread_exit(NULL);
}

void *max(void *args) {
  for (int i = 0; i < n; ++i) {
    int val = *((int *)args + i);
    if (val > max_val)
      max_val = val;
  }

  pthread_exit(NULL);
}

void *min(void *args) {
  for (int i = 0; i < n; ++i) {
    int val = *((int *)args + i);
    if (val < min_val)
      min_val = val;
  }

  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
  n = argc - 1;
  int *arr = malloc(sizeof(int) * n);
  if (arr == NULL) {
    perror("malloc failed");
    exit(1);
  }

  for (int i = 0; i < n; ++i)
    arr[i] = atoi(argv[i+1]);
  
  int mean_tid, min_tid, max_tid;
  pthread_t mean_t, min_t, max_t;

  if ((mean_tid = pthread_create(&mean_t, NULL, mean, (void *)arr)) != 0) {
    perror("thread failed");
    exit(1);
  }

  if ((min_tid = pthread_create(&min_t, NULL, min, (void *)arr)) != 0) {
    perror("thread failed");
    exit(1);
  }

  if ((max_tid = pthread_create(&max_t, NULL, max, (void *)arr)) != 0) {
    perror("thread failed");
    exit(1);
  }

  pthread_join(mean_t, NULL);
  pthread_join(min_t, NULL);
  pthread_join(max_t, NULL);

  printf("The average value is %d\n", mean_val);
  printf("The minimum value is %d\n", min_val);
  printf("The maximum value is %d\n", max_val);

  return 0;
}