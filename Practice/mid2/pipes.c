#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define RD 0
#define WR 1

int main(int argc, char *argv[]) {
  int fd[2];

  if (pipe(fd) == -1) {
    perror("pipe failed");
    exit(1);
  }

  pid_t p = fork();
  if (p == -1) {
    perror("fork failed");
    exit(1);
  }

  if (p == 0) {
    close(fd[WR]);
    char buffer[BUFSIZ];
    size_t bytes = read(fd[RD], buffer, BUFSIZ);
    buffer[bytes+1] = 0;
    printf("%s\n", buffer);
    close(fd[RD]);
  } else {
    close(fd[RD]);
    const char *message = "Hello World!\n";
    write(fd[WR], message, strlen(message) + 1);
    close(fd[WR]);
  }

  return 0;
}