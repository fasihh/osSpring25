#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg) {
  printf("Thread executing...\n");
  pthread_exit((void *)42);
}

int main() {
  pthread_t thread;
  pthread_create(&thread, NULL, thread_function, NULL);

  void *exit_status;
  pthread_join(thread, &exit_status);
  printf("Thread exited with status: %ld\n", (long)exit_status);

  return 0;
}