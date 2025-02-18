#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	pid_t process = fork();

	if (process == -1) {
		printf("process could not be forked\n");
		return 1;
	}

	if (process == 0) {
		execlp("ls", "ls", "-l", NULL);
		printf("could not execute 'ls'\n");
		return 1;
	}

	wait(NULL);
	printf("parent process ending\n");

	return 0;
}
