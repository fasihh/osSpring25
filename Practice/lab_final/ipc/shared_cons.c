#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <string.h>

#define SHM_NAME "OS"

int main()
{
	// Open shared memory
	int fd = shm_open(SHM_NAME, O_RDWR, 0666);
	if (fd == -1)
	{
		perror("shm_open failed");
		exit(1);
	}

	char *ptr = (char *)mmap(0, BUFSIZ, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (ptr == MAP_FAILED)
	{
		perror("mmap failed");
		exit(1);
	}

	int number = atoi(ptr);
	char buffer[BUFSIZ] = {0};
	int idx = 0;
	while (number)
	{
		buffer[idx++] = (number & 1) + '0';
		number >>= 1;
	}

	for (int i = 0, j = idx - 1; i < j; ++i, --j)
	{
		char temp = buffer[i];
		buffer[i] = buffer[j];
		buffer[j] = temp;
	}

	sprintf(ptr, "%s", buffer);
	ptr[strlen(buffer) + 1] = 1;

	munmap(ptr, BUFSIZ);

	return 0;
}
