#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *primes(void *arg) {
  int n = *((int *)arg) + 1;
  int *sieve = calloc(n, sizeof(int));
  if (sieve == NULL) {
    perror("calloc failed");
    exit(1);
  }

  for (int i = 2; i*i <= n; ++i) {
    if (sieve[i] == 1)
      continue;
    for (int j = 2*i; j < n; j += i)
      sieve[j] = 1;
  }

  for (int i = 2; i < n; ++i) {
    if (sieve[i] == 0)
      printf("%d ", i);
  }
  printf("\n");

  free(sieve);
  pthread_exit(0);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    perror("invalid args");
    exit(1);
  }

  int n = atoi(argv[1]);
  int tid;
  pthread_t t;
  if ((tid = pthread_create(&t, NULL, primes, (void *)&n)) != 0) {
    perror("thread failed");
    exit(1);
  }

  pthread_join(t, NULL);

  return 0;
}