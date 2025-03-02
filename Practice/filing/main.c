#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define READ_BUFFER_SIZE 5
#define WRITE_BUFFER_SIZE 100

void foo() {
	int fd = open("foo.txt", O_RDONLY | O_CREAT, 0644);

	if (fd == -1) {
		perror("failed to open/create file");
		exit(1);
	}

	char buffer[READ_BUFFER_SIZE] = {0};
	int bytes_read, total_bytes_read = 0;
	while ((bytes_read = read(fd, buffer, READ_BUFFER_SIZE-1))) {
		if (bytes_read == -1) {
			perror("failed to read from file");
			close(fd);
			exit(1);
		}

		buffer[bytes_read] = 0;
		printf("%s", buffer);
		total_bytes_read += bytes_read;
	}

	printf("\ntotal bytes read: %d\n", total_bytes_read);

	if (close(fd) == -1) {
		perror("failed to close file");
		exit(1);
	}
}

void bar(const char *text) {
	int fd = open("bar.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

	if (fd == -1) {
		perror("failed to open/create file");
		exit(1);
	}


	char buffer[WRITE_BUFFER_SIZE] = {0};

	const char *to_write = strcat(strcpy(buffer, text), "\n");

	int bytes_written = write(fd, to_write, strlen(to_write));

	printf("bytes written: %d\ntext: %s", bytes_written, buffer);

	if (bytes_written == -1) {
		perror("failed to write to file");
		exit(1);
	}

	if (close(fd) == -1) {
		perror("failed to close file");
		exit(1);
	}
}

int main(int argc, char *argv[]) {
	bar(argc > 1 ? argv[1] : "Hello World!");

	return 0;
}
