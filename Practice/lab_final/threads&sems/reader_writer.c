#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <string.h>

// reader writer where writers get exclusive access

#define lock(mtx) pthread_mutex_lock(&mtx)
#define unlock(mtx) pthread_mutex_unlock(&mtx)

#define READERS 3
#define WRITERS 3

char buffer[WRITERS][100] = {0};

volatile sig_atomic_t flag = 1;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
int reader_count = 0;
sem_t rw;

const char *words[4] = {"Hello", "World", "Goodbye", "727"};

void *writer(void *arg) {
  int idx = (long)arg;

  while (flag) {
    sem_wait(&rw);
    const char* word = words[rand() % 4];
    printf("writer #%d writes: %s\n\n", idx, word);
    strcpy(buffer[idx], word);
    sem_post(&rw);
    sleep(1 + rand() % 3);
  }
}

void *reader(void *arg) {
  int idx = (long)arg;

  while (flag) {
    lock(mtx);
    reader_count++;
    if (reader_count == 1)
      sem_wait(&rw);
    unlock(mtx);

    printf("reader #%d reads:\n", idx+1);
    for (int i = 0; i < WRITERS; ++i)
      printf("\t%s\n", buffer[i]);
    printf("\n");

    lock(mtx);
    reader_count--;
    if (reader_count == 0)
      sem_post(&rw);
    unlock(mtx);

    sleep(1 + rand() % 5);
  }
}

void sig_handler(int sig) {
  if (sig == SIGINT)
    flag = 0;
}

int main() {
  if (signal(SIGINT, sig_handler) == SIG_ERR) {
    perror("failed to create signal");
    exit(1);
  }

  pthread_t readers[READERS], writers[WRITERS];
  sem_init(&rw, 0, 1);

  for (int i = 0; i < WRITERS; ++i)
    pthread_create(&writers[i], NULL, writer, (void *)i);
  for (int i = 0; i < READERS; ++i)
    pthread_create(&readers[i], NULL, reader, (void *)i);

  for (int i = 0; i < WRITERS; ++i)
    pthread_join(writers[i], NULL);
  for (int i = 0; i < READERS; ++i)
    pthread_join(readers[i], NULL);

  pthread_mutex_destroy(&mtx);
  sem_destroy(&rw);

  return 0;
}