#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define RD 0
#define WR 1

int main() {
	int fd[2];
	if (pipe(fd) == -1) {
		perror("pipe failed");
		exit(1);
	}

	int child1 = fork();
	if (child1 == 0) {
		close(fd[RD]);
		const char *message1 = "Hello ";
		write(fd[WR], message1, strlen(message1));
		close(fd[WR]);

		exit(0);
	}

	int child2 = fork();
	if (child2 == 0) {
		close(fd[RD]);
		const char *message2 = "World!";
		write(fd[WR], message2, strlen(message2));
		close(fd[WR]);

		exit(0);
	}

	char buffer[256];

	close(fd[WR]);
	int bytes_read = read(fd[RD], buffer, sizeof(buffer));
	buffer[bytes_read] = 0;
	printf("%s\n", buffer);
	close(fd[RD]);

	return 0;
}
