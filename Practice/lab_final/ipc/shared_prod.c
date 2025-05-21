#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <string.h>

#define SHM_NAME "OS"

int main(int argc, char *argv[]) {
  if (argc != 2) {
		fprintf(stderr, "usage: %s <number>\n", argv[0]);
		exit(1);
	}

  int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
  ftruncate(fd, BUFSIZ);

  char *ptr = (char *)mmap(0, BUFSIZ, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  int n = strlen(argv[1]);
  sprintf(ptr, "%s", argv[1]);
  ptr[n+1] = 0;

  while (ptr[n+1] == 0) usleep(100);

  printf("%s\n", ptr);

  munmap(ptr, BUFSIZ);
  shm_unlink(SHM_NAME);

  return 0;
}
