#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FIFO_NAME "/tmp/fifo"

int main() {
	const char *message = "Hello World";

	mkfifo(FIFO_NAME, 0666);

	int fd = open(FIFO_NAME, O_WRONLY);

	if (fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	int bytes_written = write(fd, message, strlen(message));

	if (bytes_written == -1) {
		perror("write");
		exit(EXIT_FAILURE);
	}

	close(fd);
	unlink(FIFO_NAME);

	return 0;
}
