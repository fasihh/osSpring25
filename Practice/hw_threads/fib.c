#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

int N = 0;
int *fib = NULL;

void *fib_runner(void *arg) {
  int n = *((int *)arg);

  if (n == 0) {
    fib[0] = 0;
  } else if (n == 1) {
    fib[1] = 1;
  } else {
    while (fib[n-1] == -1 || fib[n-2] == -1);
    fib[n] = fib[n-1] + fib[n-2];
  }

  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    perror("invalid args");
    exit(1);
  }

  N = atoi(argv[1]);
  fib = calloc(N, sizeof(int));
  assert(fib != NULL);

  for (int i = 0; i < N; ++i)
    fib[i] = -1;

  pthread_t threads[N];
  int thread_args[N];

  for (int i = 0; i < N; ++i) {
    thread_args[i] = i;
    assert(pthread_create(threads + i, NULL, fib_runner, (void *)&thread_args[i]) == 0);
  }

  for (int i = 0; i < N; ++i)
    pthread_join(threads[i], NULL);

  for (int i = 0; i < N; ++i)
    printf("%d ", fib[i]);
  printf("\n");
  printf("%f\n", (float)fib[N-1]/fib[N-2]);

  return 0;
}