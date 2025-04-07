#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>

#define SHM_NAME "OS"

int main(int argc, char *argv[]) {
  char buffer[BUFSIZ] = {0};

  int fd = shm_open(SHM_NAME, O_RDONLY, 0666);

  char *ptr = (char *)mmap(0, BUFSIZ, PROT_READ, MAP_SHARED, fd, 0);

  printf("%s\n", ptr);

  shm_unlink(SHM_NAME);

  return 0;
}