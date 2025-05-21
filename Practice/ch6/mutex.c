#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <unistd.h>

atomic_int idx = 0;
char *messages[2] = {"thread_A", "thread_B"};

pthread_mutex_t lock;

void *runner(void *arg) {
  int i = (long)arg;

  while (1) {
    pthread_testcancel();

    pthread_mutex_lock(&lock);
    printf("enter critical section: %s\n", messages[i]);
    atomic_store(&idx, i);
    sleep(1);
    pthread_mutex_unlock(&lock);
  }
}

void *reader(void *arg) {
  while (1) {
    int current_idx = atomic_load(&idx);
    printf("\treader: %s\n", messages[current_idx]);
    pthread_testcancel();
    sleep(1);
  }
}

int main() {
  pthread_t thread_a, thread_b, thread_runner;

  pthread_create(&thread_a, NULL, runner, (void *)0);
  pthread_create(&thread_b, NULL, runner, (void *)1);
  pthread_create(&thread_runner, NULL, reader, NULL);

  for (int i = 0; i < 10; ++i) sleep(2);

  pthread_cancel(thread_a);
  pthread_cancel(thread_b);
  pthread_cancel(thread_runner);

  pthread_join(thread_a, NULL);
  pthread_join(thread_b, NULL);
  pthread_join(thread_runner, NULL);

  return 0;
}