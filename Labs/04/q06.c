#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void handle_alarm(int signum) {
    printf("process ending graefully\n");
    exit(0);
}

int main() {
    signal(SIGALRM, handle_alarm);
    alarm(5);

    while (1) {
        printf("Hello World\n");
        sleep(1);
    }

    return 0;
}
