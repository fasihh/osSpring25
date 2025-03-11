#include <stdio.h>
#include <stdlib.h>
#include "temperature.h"

int main(int argc, char *argv[]) {
	printf("%fC %fF\n", convert_f_to_c(atof(argv[1])), convert_c_to_f(atof(argv[2])));

	return 0;
}
