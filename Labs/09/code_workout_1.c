#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function
void sigint_handler(int signum) {
  fprintf(stdout, "Caught SIGINT signal (%d)\n", signum);
  raise(SIGKILL);
}

void my_handler(int signum) {
  fprintf(stdout, "Caught SIGUSR1 signal (%d)\n", signum);
  raise(SIGKILL);
}

int main() {
  // Registering signal handler for SIGINT
  if (signal(SIGINT, sigint_handler) == SIG_ERR) {
    printf("Error setting up signal handler for SIGINT\n");
    return 1;
  }

  if (signal(SIGUSR1, my_handler) == SIG_ERR) {
    printf("Error setting up signal handler for SIGUSR1\n");
    return 1;
  }

  printf("Press Ctrl+C to send a SIGINT signal\n");

  kill(getpid(), SIGUSR1);
  // Infinite loop to keep the program running
  // while(1) {
  //   sleep(1);
  // }
  return 0;
}
