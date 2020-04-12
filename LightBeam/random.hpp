#pragma once

#include <cstdlib>


inline double random_double() {
	// Returns a random double in [0,1)
	return rand() / (RAND_MAX + 1.0);
}


inline double random_double(double min, double max) {
	// Returns a random double in [min, max)
	return min + (max - min) * random_double();
}