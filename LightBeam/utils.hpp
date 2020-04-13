#pragma once


#define _USE_MATH_DEFINES
#include <math.h>


namespace LightBeam
{
	namespace Util
	{
		inline double clamp(double x, double min, double max) {
			if (x < min) return min;
			if (x > max) return max;
			return x;
		}


		inline double degrees_to_radians(double degrees) {
			return degrees * M_PI / 180.0;
		}

		inline double ffmin(double a, double b) {
			return a <= b ? a : b;
		}

		inline double ffmax(double a, double b) {
			return a >= b ? a : b;
		}
	}
}