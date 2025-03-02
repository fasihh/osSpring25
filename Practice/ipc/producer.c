#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define SHM_NAME "OS_SHM"
#define SHM_SIZE 4096

int main() {
    // Create and configure shared memory
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("producer: shm_open failed");
        exit(EXIT_FAILURE);
    }

    // Set size of shared memory
    if (ftruncate(shm_fd, SHM_SIZE) == -1) {
        perror("producer: ftruncate failed");
        shm_unlink(SHM_NAME);
        exit(EXIT_FAILURE);
    }

    // Map shared memory into address space
    char *shm_ptr = mmap(0, SHM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("producer: mmap failed");
        shm_unlink(SHM_NAME);
        exit(EXIT_FAILURE);
    }

    // Write data to shared memory
    const char *message = "Hello from the producer!";
    snprintf(shm_ptr, SHM_SIZE, "%s", message);
    printf("Producer: Written to shared memory: %s\n", message);

    // Launch Python consumer
    pid_t pid = fork();
    if (pid == -1) {
        perror("producer: fork failed");
        shm_unlink(SHM_NAME);
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process: Run Python consumer
        execlp("python3", "python3", "consumer.py", NULL);
        perror("producer: execlp failed");
        shm_unlink(SHM_NAME);
        exit(EXIT_FAILURE);
    }

    // Parent process: Wait for the consumer to finish
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
        printf("Producer: Consumer exited with status: %d\n", WEXITSTATUS(status));
    } else {
        printf("Producer: Consumer did not exit successfully.\n");
    }

    // Cleanup
    if (shm_unlink(SHM_NAME) == -1) {
        perror("producer: shm_unlink failed");
        exit(EXIT_FAILURE);
    }

    printf("Producer: Shared memory cleaned up.\n");

    return 0;
}
