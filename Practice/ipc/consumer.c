#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define BUFFER_SIZE 4096

int main() {
	const char* name = "OS";

	int fd = shm_open(name, O_RDONLY, 0666);

	if (fd == -1) {
		perror("consumer: shm_open failed");
		exit(1);
	}

	char *ptr = (char *)mmap(0, BUFFER_SIZE, PROT_READ, MAP_SHARED, fd, 0);

	if (ptr == MAP_FAILED) {
		perror("consumer: mmap failed");
		exit(1);
	}

	printf("from producer to consumer: %s\n", (char *)ptr);

	if (munmap(ptr, BUFFER_SIZE) == -1)
		perror("consumer: unmap failed");

	close(fd);

	return 0;
}
