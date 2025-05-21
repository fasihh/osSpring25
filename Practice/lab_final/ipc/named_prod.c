#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FIFO_P "/tmp/pfifo"
#define FIFO_C "/tmp/cfifo"

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <number>\n", argv[0]);
		exit(1);
	}

	mkfifo(FIFO_P, 0666);

	int fd = open(FIFO_P, O_WRONLY);

	if (fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	int bytes_written = write(fd, argv[1], strlen(argv[1]));

	if (bytes_written == -1) {
		perror("write");
		exit(EXIT_FAILURE);
	}

	close(fd);

	fd = open(FIFO_C, O_RDONLY);

	if (fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	char buffer[BUFSIZ];
	int bytes_read = read(fd, buffer, BUFSIZ);

	if (bytes_read == -1) {
		perror("read");
		exit(EXIT_FAILURE);
	}

	close(fd);

	printf("%s\n", buffer);

	unlink(FIFO_P);

	return 0;
}
