#pragma once

#include <functional>
#include <random>


inline double random_double() {
	// Returns a random double in [0,1)
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	static std::function<double()> rand_generator =
		std::bind(distribution, generator);

	return rand_generator();
}


inline double random_double(double min, double max) {
	// Returns a random double in [min, max)
	return min + (max - min) * random_double();
}