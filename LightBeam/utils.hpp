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

		inline double trilinear_interp(
			double c[2][2][2], double u, double v, double w)
		{
			auto accum = 0.0;

			for (auto i = 0; i < 2; i++)
				for (auto j = 0; j < 2; j++)
					for (auto k = 0; k < 2; k++)
						accum += (i * u + (1.0 - i) * (1.0 - u))
							   * (j * v + (1.0 - j) * (1.0 - v))
						       * (k * w + (1.0 - k) * (1.0 - w))
						       * c[i][j][k];

			return accum;
		}
	}
}