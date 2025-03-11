#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define FIFO_NAME "/tmp/fifo"

int main() {

	int fd = open(FIFO_NAME, O_RDONLY);

	if (fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	char buffer[BUFSIZ] = {0};
	int bytes_read = read(fd, buffer, BUFSIZ);

	if (bytes_read == -1) {
		perror("read");
		exit(EXIT_FAILURE);
	}

	printf("%s\n", buffer);

	close(fd);

	return 0;
}
