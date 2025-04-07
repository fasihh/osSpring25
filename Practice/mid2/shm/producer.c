#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>

#define SHM_NAME "OS"

int main(int argc, char *argv[]) {
  const char *message = "Hello World!";

  int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
  ftruncate(fd, BUFSIZ);

  char *ptr = (char *)mmap(0, BUFSIZ, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  sprintf(ptr, "%s", message);
  sprintf(ptr, "%s %s", ptr, message);

  return 0;
}
