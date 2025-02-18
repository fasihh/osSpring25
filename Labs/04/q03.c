#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void display_uid() {
	printf("uid: %d\n", getuid());
}

int main() {
	pid_t process = fork();

	if (process == -1) {
		printf("failed to fork process");
		return 1;
	}

	if (process == 0) {
		printf("process id: %d\n", getpid());
		printf("parent process id: %d\n", getppid());
		return 0;
	}

	display_uid();
	printf("ending parent process\n");

	return 0;
}
