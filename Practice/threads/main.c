#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 2

typedef struct {
	int id, l, r;
} accumulate_args;

int sum = 0;

void *accumulate(void *param) {
	accumulate_args *args = (accumulate_args *) param;
	printf("thread#: %d\n", args->id);
	for (int i = args->l + 1; i <= args->r; ++i) {
		printf("%d\n", i);
		sum += i;
	}

	free(args);
	pthread_exit(0);
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		perror("usage: ./main <n>");
		exit(1);
	}

	pthread_t workers[NUM_THREADS];

	int l = 0, r = atoi(argv[1]) / NUM_THREADS; // 10 / 2 = 5
	int step = r;
	for (int i = 0; i < NUM_THREADS; ++i) {
		// thread init
		pthread_t tid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		// arg setting
		accumulate_args *args = malloc(sizeof(accumulate_args));
		args->id = i, args->l = l, args->r = r;
		l = r, r += step;

		// thread creation
		pthread_create(&tid, &attr, accumulate, (void *) args);
		workers[i] = tid;
	}

	for (int i = 0; i < NUM_THREADS; ++i)
		pthread_join(workers[i], NULL);

	printf("sum: %d\n", sum);

	return 0;
}
