#pragma once


#define _USE_MATH_DEFINES
#include <math.h>


inline double clamp(double x, double min, double max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}


inline double degrees_to_radians(double degrees) {
	return degrees * M_PI / 180.0;
}