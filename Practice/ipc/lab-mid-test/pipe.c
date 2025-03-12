#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define RD 0
#define WR 1

int main() {
	char buffer[BUFSIZ];
	int pages;
	scanf("%d", &pages);
	
	int fd[2];
	if (pipe(fd) == -1) {
		perror("pipe");
		exit(1);
	}

	sprintf(buffer, "%d", pages);
	write(fd[WR], buffer, strlen(buffer));
	close(fd[WR]);

	int id = fork();
	if (id == -1) {
		perror("fork");
		exit(1);
	}

	if (id == 0) {
		char cbuffer[BUFSIZ];
		int br = read(fd[RD], cbuffer, BUFSIZ);
		cbuffer[br] = 0;
		close(fd[RD]);
		
		double duty = 1.5 * atof(cbuffer);

		sprintf(cbuffer, "%f", duty);
		write(fd[WR], cbuffer, strlen(cbuffer));
		close(fd[WR]);

		exit(0);
	}

	wait(NULL);

	close(fd[WR]);
	int br = read(fd[RD], buffer, BUFSIZ);
	buffer[br] = 0;
	close(fd[RD]);

	double final = 1.02 * atof(buffer);

	printf("%f\n", final);

	return 0;
}
