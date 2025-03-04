#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main() {
	int fd = open("input.txt", O_RDWR | O_CREAT, 0644);

	if (fd == -1) {
		perror("failed to open file");
		exit(1);
	}

	char buffer[BUFFER_SIZE];
	if (read(fd, buffer, BUFFER_SIZE) == -1) {
		perror("failed to read");
		exit(1);
	}

	pid_t child = fork();

	if (child == -1) {
		perror("failed to fork");
		exit(1);
	}

	if (child == 0) {
		const char *new_content = "Processed by child process\n";

		if (write(fd, new_content, strlen(new_content)) == -1) {
			perror("failed to write");
			exit(1);
		}

		close(fd);

		execlp("cat", "cat", "input.txt", NULL);
		perror("execlp failed");
		exit(1);
	}

	wait(NULL);

	close(fd);

	return 0;
}
