#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define RE 0
#define WE 1
#define PW_P 0
#define CW_P 1

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "usage: %s <number>\n", argv[0]);
    exit(1);
  }

  int fd[2][2];

  if (pipe(fd[PW_P]) == -1 || pipe(fd[CW_P]) == -1) {
    perror("pipe failed");
    exit(1);
  }

  pid_t child = fork();
  if (child == -1) {
    perror("fork failed");
    exit(1);
  } else if (child == 0) {
    
    char buffer[BUFSIZ];
    close(fd[PW_P][WE]);
    ssize_t bytes_read = read(fd[PW_P][RE], buffer, BUFSIZ);
    if (bytes_read == -1) {
      perror("failed to read");
      exit(1);
    }
    close(fd[PW_P][RE]);
    buffer[bytes_read] = 0;
    printf("%s\n", buffer);

    int idx = 0;
    int number = atoi(buffer);
    while (number) {
      buffer[idx++] = (number & 1) + '0';
      number >>= 1;
    }
    for (int i = 0, j = idx-1; i < idx/2; ++i, --j) {
      buffer[i] ^= buffer[j];
      buffer[j] ^= buffer[i];
      buffer[i] ^= buffer[j];
    }
    buffer[idx] = 0;

    close(fd[CW_P][RE]);
    ssize_t bytes_written = write(fd[CW_P][WE], buffer, idx);
    if (bytes_written == -1) {
      perror("failed to write");
      exit(1);
    }
    close(fd[CW_P][WE]);
  } else {
    close(fd[PW_P][RE]);
    ssize_t bytes_written = write(fd[PW_P][WE], argv[1], strlen(argv[1]));
    if (bytes_written == -1) {
      perror("failed to write");
      exit(1);
    }
    close(fd[PW_P][WE]);

    wait(NULL);

    char buffer[BUFSIZ];
    close(fd[CW_P][WE]);
    ssize_t bytes_read = read(fd[CW_P][RE], buffer, BUFSIZ);
    if (bytes_read == -1) {
      perror("failed to read");
      exit(1);
    }
    close(fd[CW_P][RE]);

    printf("%s\n", buffer);
  }

  return 0;
}