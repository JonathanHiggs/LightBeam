#pragma once


#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>

#include "Random.hpp"


namespace LightBeam
{
	namespace Math
	{
		class Vec3 {
		private:
			double _data[3];

		public:
			Vec3() : _data{ 0, 0, 0 }
			{}

			Vec3(double x, double y, double z)
				: _data{ x, y, z }
			{}

			Vec3(const Vec3& v) noexcept
				: _data{ v._data[0], v._data[1], v._data[2] }
			{}

			static const Vec3 nan;
			static const Vec3 one;
			static const Vec3 zero;
			static const Vec3 unit_x;
			static const Vec3 unit_y;
			static const Vec3 unit_z;


			double x() const noexcept { return _data[0]; }
			double y() const noexcept { return _data[1]; }
			double z() const noexcept { return _data[2]; }


			Vec3 operator -() const { return Vec3(-_data[0], -_data[1], -_data[2]); }

			double operator[](int axis) const { return _data[axis]; }


			double length() const {
				return std::sqrt(length_squared());
			}

			double length_squared() const {
				return _data[0] * _data[0] + _data[1] * _data[1] + _data[2] * _data[2];
			}

			Vec3 norm() const {
				return *this / length();
			}

			friend std::ostream& operator <<(std::ostream& out, const Vec3& v);
			friend Vec3 operator+(const Vec3& u, const Vec3& v);
			friend Vec3 operator-(const Vec3& u, const Vec3& v);
			friend Vec3 operator*(const Vec3& u, const Vec3& v);
			friend Vec3 operator*(double t, const Vec3& v);
			friend Vec3 operator*(const Vec3& v, double t);
			friend Vec3 operator/(const Vec3& v, double t);

			static double dot(const Vec3& u, const Vec3& v) {
				return u._data[0] * v._data[0]
					+ u._data[1] * v._data[1]
					+ u._data[2] * v._data[2];
			}

			static Vec3 cross(const Vec3& u, const Vec3& v) {
				return Vec3(
					u._data[1] * v._data[2] - u._data[2] * v._data[1],
					u._data[2] * v._data[0] - u._data[0] * v._data[2],
					u._data[0] * v._data[1] - u._data[1] * v._data[0]);
			}

			static Vec3 interpolate(const Vec3& u, const Vec3& v, double t) {
				return (1.0 - t) * u + t * v;
			}

			static Vec3 random() {
				return Vec3(
					Util::random_double(),
					Util::random_double(),
					Util::random_double());
			}

			static Vec3 random(double min, double max) {
				return Vec3(
					Util::random_double(min, max),
					Util::random_double(min, max),
					Util::random_double(min, max));
			}

			static Vec3 random_in_unit_sphere() {
				while (true) {
					const auto p = Vec3::random(-1, 1);
					if (p.length_squared() >= 1) continue;
					return p;
				}
			}

			static Vec3 random_unit_vector() {
				const auto a = Util::random_double(0.0, 2.0 * M_PI);
				const auto z = Util::random_double(-1, 1);
				const auto r = sqrt(1.0 - z * z);
				return Vec3(r * std::cos(a), r * std::sin(a), z);
			}

			static Vec3 random_in_hemisphere(const Vec3& normal) {
				Vec3 in_unit_sphere = random_in_unit_sphere();
				if (dot(in_unit_sphere, normal) > 0.0)
					return -in_unit_sphere;
				return in_unit_sphere;
			}

			static Vec3 reflect(const Vec3& vec, const Vec3& normal) {
				return vec - 2 * dot(vec, normal) * normal;
			}

			static Vec3 refract(const Vec3& uv, const Vec3& normal, double etai_over_etat) {
				const auto cos_theta = dot(-uv, normal);
				const auto out_parallel = etai_over_etat * (uv + cos_theta * normal);
				const auto out_perp = -sqrt(1.0 - out_parallel.length_squared()) * normal;
				return out_parallel + out_perp;
			}
		};
	}
}