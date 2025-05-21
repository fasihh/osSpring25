#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_P "/tmp/pfifo"
#define FIFO_C "/tmp/cfifo"

int main() {
  mkfifo(FIFO_C, 0666);

	int fd = open(FIFO_P, O_RDONLY);

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

	close(fd);

  int idx = 0;
  int number = atoi(buffer);
  while (number) {
    buffer[idx++] = (number & 1) + '0';
    number >>= 1;
  }

  for (int i = 0, j = idx - 1; i < j; ++i, --j) {
    char temp = buffer[i];
    buffer[i] = buffer[j];
    buffer[j] = temp;
  }
  buffer[idx] = '\0';

  fd = open(FIFO_C, O_WRONLY);

	int bytes_written = write(fd, buffer, BUFSIZ);

	if (bytes_written == -1) {
		perror("write");
		exit(EXIT_FAILURE);
	}

  close(fd);
  
  unlink(FIFO_C);

	return 0;
}
