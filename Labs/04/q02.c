#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
	pid_t process = fork();

	if (process == -1) {
		printf("failed to fork process");
		return 1;
	}
	
	for (int i = 0; i < 100; ++i)
		printf("I am a %s process\n", process ? "parent" : "child");

	return 0;
}
