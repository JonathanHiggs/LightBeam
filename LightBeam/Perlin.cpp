#include "Perlin.hpp"
#include "Random.hpp"
#include "utils.hpp"


using namespace LightBeam::Math;


namespace LightBeam
{
	namespace Noise
	{

		Perlin::Perlin()
		{
			vecs = std::vector<Vec3>(point_count);
			for (int i = 0; i < point_count; ++i)
				vecs[i] = Vec3::random(-1, 1);

			x_data = generate_permutation();
			y_data = generate_permutation();
			z_data = generate_permutation();
		}

		double Perlin::noise(const Math::Vec3& point) const
		{
			auto u = point.x() - std::floor(point.x());
			auto v = point.y() - std::floor(point.y());
			auto w = point.z() - std::floor(point.z());

			auto i = static_cast<int>(std::floor(point.x()));
			auto j = static_cast<int>(std::floor(point.y()));
			auto k = static_cast<int>(std::floor(point.z()));

			Vec3 c[2][2][2];

			for (auto di = 0; di < 2; di++)
				for (auto dj = 0; dj < 2; dj++)
					for (auto dk = 0; dk < 2; dk++)
						c[di][dj][dk] = vecs[
							x_data[(i + di) & 255]
							^ y_data[(j + dj) & 255]
							^ z_data[(k + dk) & 255]];

			return perlin_interp(c, u, v, w);
		}

		double Perlin::coarse_noise(const Vec3& point) const
		{
			auto i = static_cast<int>(4 * point.x()) & 255;
			auto j = static_cast<int>(4 * point.y()) & 255;
			auto k = static_cast<int>(4 * point.z()) & 255;

			auto vec = vecs[x_data[i] ^ y_data[j] ^ z_data[k]];

			return Vec3::dot(vec, Vec3::one);
		}

		double Perlin::turb(const Vec3& point, int depth) const
		{
			auto accum = 0.0;
			auto temp = point;
			auto weight = 1.0;

			for (int i = 0; i < depth; i++)
			{
				accum += weight * noise(temp);
				weight *= 0.5;
				temp = temp * 2;
			}

			return std::abs(accum);
		}

		std::vector<int> Perlin::generate_permutation()
		{
			auto data = std::vector<int>(point_count);

			for (auto i = 0; i < point_count; i++)
				data[i] = i;

			permute(point_count, data);

			return data;
		}

		void Perlin::permute(int point_count, std::vector<int>& data)
		{
			for (int i = point_count - 1; i > 0; i--) {
				int target = Util::random_int(0, i);
				int temp = data[i];
				data[i] = data[target];
				data[target] = temp;
			}
		}

		double Perlin::perlin_interp(Vec3 c[2][2][2], double u, double v, double w)
		{
			auto uu = u * u * (3 - 2 * u);
			auto vv = v * v * (3 - 2 * v);
			auto ww = w * w * (3 - 2 * w);
			auto accum = 0.0;

			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 2; j++)
					for (int k = 0; k < 2; k++)
					{
						auto weight = Vec3(u - i, v - j, w - k);
						accum += (i * uu + (1 - i) * (1 - uu))
							   * (j * vv + (1 - j) * (1 - vv))
							   * (k * ww + (1 - k) * (1 - ww))
							   * Vec3::dot(c[i][j][k], weight);
					}

			return accum;
		}
	}
}