#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <unistd.h>

void proc_exit() {
  int wstat;
  pid_t pid;

  printf("proc_exit: %d\n", getpid());

  while (1) {
    // Get info about child process.
    // WNOHANG returns immediately if there is no child to wait
    pid = wait3(&wstat, WNOHANG, NULL);
    if (pid == 0 || pid == -1) {
      fprintf(stdout, "return value of wait3() is %d\n", pid);
      return;
    }
    fprintf(stdout, "Return code: %d\n", WEXITSTATUS(wstat));
  }
}

int main() {
  signal(SIGCHLD, proc_exit);
  for (int i = 0; i < 3; i++) {
    switch (fork()) {
      case -1:
        perror("main: fork");
        exit(0);
      case 0:
        printf("Child %d (PID: %d) is alive\n", i+1, getpid());
        int ret_code = rand() % 100;  // Smaller random number for readability
        sleep(1);  // Ensure children don't terminate too quickly
        printf("Child %d exiting with code %d\n", i+1, ret_code);
        exit(ret_code);
      default:
        break;
    }
  }

  printf("Parent (sleeping): %d\n", getpid());
  sleep(5);
  printf("Parent (resuming): %d\n", getpid());
  
  exit(0);
}
