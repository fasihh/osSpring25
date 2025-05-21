#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>

int turn = 0;
int flags[2] = {0};

char *messages[2] = {"thread_A", "thread_B"};
atomic_int idx = 0;

pthread_mutex_t lock;

void *runner(void *arg) {
  int i = (long)arg;
  int j = 1 - i;

  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

  while (1) {
    flags[i] = 1;
    turn = j;
    while (flags[j] && turn == j) pthread_testcancel();
    // start critical
    pthread_mutex_lock(&lock);
    printf("entered critical section: %s\n", messages[i]);
    atomic_store(&idx, i);
    sleep(1);
    pthread_mutex_unlock(&lock);
    // end critical
    flags[i] = 0;
  }
}

void *reader(void *arg) {
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

  while (1) {
    int current_idx = atomic_load(&idx);
    printf("\treader: %s\n", messages[current_idx]);
    pthread_testcancel();
    sleep(1);
  }
}

int main() {
  pthread_t thread_a, thread_b, thread_reader;

  pthread_create(&thread_a, NULL, runner, (void *)0);
  pthread_create(&thread_b, NULL, runner, (void *)1);
  pthread_create(&thread_reader, NULL, reader, NULL);

  for (int i = 0; i < 10; ++i) sleep(2);

  pthread_cancel(thread_a);
  pthread_cancel(thread_b);
  pthread_cancel(thread_reader);

  pthread_join(thread_a, NULL);
  pthread_join(thread_b, NULL);
  pthread_join(thread_reader, NULL);

  return 0;
}
