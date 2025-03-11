#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#define RD 0
#define WR 1

int main() {
	char buffer[256] = {0};
	int fd[2];
	if (pipe(fd) == -1) {
		perror("pipe");
		exit(1);
	}

	int child = fork();
	if (child == 0) {
		int arr[] = {1, 2, 3, 4, 5};
		
		for (int i = 0; i < 5; ++i)
			sprintf(buffer, "%s%d ", buffer, arr[i]);

		close(fd[RD]);
		write(fd[WR], buffer, strlen(buffer));
		close(fd[WR]);
		
		exit(0);
	}

	wait(NULL);

	close(fd[WR]);
	int bytes_read = read(fd[RD], buffer, sizeof(buffer));
	buffer[bytes_read] = 0;

	char *tok = strtok(buffer, " ");
	while (tok) {
		printf("%d\n", atoi(tok));
		tok = strtok(NULL, " ");
	}

	return 0;
}
