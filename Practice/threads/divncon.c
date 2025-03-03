#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THRESHOLD 2

typedef struct {
	int l;
	int r;
	int sum;
} compute_args;

void *compute(void *params) {
	compute_args *args = (compute_args *) params;

	if (args->r - args->l <= THRESHOLD) {
		args->sum = (args->r - args->l + 1) * (args->r + args->l) / 2;
		printf("[%d, %d]: %d\n", args->l, args->r, args->sum);
		pthread_exit(0);
	}

	int mid = args->l + (args->r - args->l) / 2;

	compute_args left_args = {args->l, mid, 0}, right_args = {mid+1, args->r, 0};

	pthread_t left, right;

	pthread_create(&left, NULL, compute, (void *)&left_args);
	pthread_create(&right, NULL, compute, (void *)&right_args);

	pthread_join(left, NULL);
	pthread_join(right, NULL);	

	args->sum = left_args.sum + right_args.sum;

	pthread_exit(0);
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <N>\n", argv[0]);
		exit(1);
	}

	int N = atoi(argv[1]);
	compute_args args = {1, N, 0};

	pthread_t root;
	pthread_create(&root, NULL, compute, (void *)&args);
	pthread_join(root, NULL);

	printf("sum: %d\n", args.sum);

	return 0;
}
