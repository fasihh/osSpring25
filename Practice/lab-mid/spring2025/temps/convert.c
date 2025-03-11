#include "temperature.h"

const double convert_f_to_c(const double f) {
	// F = C * 1.8 + 32
	// (C - 32) / 1.8 = F
	return (double) (f - C) / K;
}

const double convert_c_to_f(const double c) {
	return c * K + C;
}
