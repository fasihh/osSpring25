#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <assert.h>

#define FIFO_NAME "/tmp/OS"

int main(int argc, char *argv[]) {

  mkfifo(FIFO_NAME, 0666);
  pid_t p = fork();
  if (p == -1) {
    perror("fork failed");
    exit(1);
  }

  if (p == 0) {
    int fd = open(FIFO_NAME, O_RDONLY);

    char buffer[BUFSIZ] = {0};

    int bytes = read(fd, buffer, BUFSIZ);
    assert(bytes != -1);

    buffer[bytes + 1] = 0;

    printf("%d: %s\n", getpid(), buffer);

  } else {
    int fd = open(FIFO_NAME, O_WRONLY);

    char buffer[BUFSIZ] = {0};

    sprintf(buffer, "Hello World! from %d", getpid());

    assert(write(fd, buffer, strlen(buffer) + 1) != -1);
    
    wait(NULL);

    close(fd);
  }

  return 0;
}