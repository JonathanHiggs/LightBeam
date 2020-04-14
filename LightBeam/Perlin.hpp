#pragma once


#include <vector>

#include "Vec3.hpp"



namespace LightBeam
{
	namespace Noise
	{

		class Perlin {
		private:
			std::vector<Math::Vec3> vecs;
			std::vector<int> x_data;
			std::vector<int> y_data;
			std::vector<int> z_data;

		public:
			Perlin();

			double noise(const Math::Vec3& point) const;

			double coarse_noise(const Math::Vec3& point) const;

			double turb(const Math::Vec3& point, int depth = 7) const;


		private:

			static const int point_count = 256;

			static std::vector<int> generate_permutation();
			static void permute(int point_count, std::vector<int>& data);
			static double perlin_interp(Math::Vec3 c[2][2][2], double u, double v, double w);
		};

	}
}