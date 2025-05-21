#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

#define ROOMS 3
#define CAPACITY 3
#define STUDENTS 5

volatile sig_atomic_t flag = 1;
pthread_mutex_t mtx;
sem_t empty;

int rooms[ROOMS] = {0};

void *student(void *arg) {
  int idx = (long)arg;
  while (flag) {
    int assigned = -1;
    pthread_mutex_lock(&mtx);
    for (int i = 0; i < ROOMS; ++i) {
      if (rooms[i] == CAPACITY)
        continue;
      assigned = i;
      rooms[i]++;
      break;
    }
    pthread_mutex_unlock(&mtx);

    if (assigned != -1) {
      sem_wait(&empty);
      printf("student #%d occupies room #%d: (%d/%d)\n", idx, assigned, rooms[assigned], CAPACITY);
      sleep(1 + rand() % 4);
      printf("student #%d leaves room #%d\n", idx, assigned, rooms[assigned], CAPACITY);
      sem_post(&empty);
    }

    pthread_mutex_lock(&mtx);
    rooms[assigned]--;
    pthread_mutex_unlock(&mtx);
    
    sleep(1 + rand() % 4);
  }
}

void sig_handler(int sig) {
  if (sig == SIGINT) {
    flag = 0;
  }
}

int main() {
  if (signal(SIGINT, sig_handler) == SIG_ERR) {
    perror("failed to create signal");
    exit(1);
  }

  pthread_mutex_init(&mtx, NULL);
  sem_init(&empty, 0, ROOMS * CAPACITY);

  pthread_t students[STUDENTS];

  for (int i = 0; i < STUDENTS; ++i)
    pthread_create(&students[i], NULL, student, (void *)i);

  for (int i = 0; i < STUDENTS; ++i)
    pthread_join(students[i], NULL);

  sem_destroy(&empty);
  pthread_mutex_destroy(&mtx);

  return 0;
}