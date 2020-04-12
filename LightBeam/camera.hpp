#pragma once


#include "ray.hpp"
#include "vec3.hpp"
#include "random.hpp"
#include "utils.hpp"


class Camera {
private:
	Vec3 _origin;
	Vec3 _center;
	Vec3 _horizontal;
	Vec3 _vertical;

public:
	Camera(
		const Vec3& origin,
		const Vec3& center,
		const Vec3& horizontal,
		const Vec3& vertical)
		: _origin{origin}
		, _center{center}
		, _horizontal{horizontal}
		, _vertical{vertical}
	{ }

	static Camera from_vfov(
		const Vec3& from,
		const Vec3& at,
		const Vec3& up,
		double vfov,
		double aspect_ratio)
	{
		const auto theta = degrees_to_radians(vfov);
		const auto half_height = std::tan(theta / 2.0);
		const auto half_width = aspect_ratio * half_height;

		return _from(from, at, up, half_width, half_height);
	}

	static Camera from_hfov(
		const Vec3& from,
		const Vec3& at,
		const Vec3& up,
		double hfov,
		double aspect_ratio)
	{
		auto theta = degrees_to_radians(hfov);
		auto half_width = std::tan(theta / 2.0);
		auto half_height = half_width / aspect_ratio;

		return _from(from, at, up, half_width, half_height);
	}


	Ray get_ray(double u, double v) {
		return Ray(_origin, _center + u * _horizontal + v * _vertical - _origin);
	}

private:
	static Camera _from(
		const Vec3& from,
		const Vec3& at,
		const Vec3& up,
		double half_width,
		double half_height)
	{
		// get the orthonormal basis
		const auto w = (from - at).norm();
		const auto u = cross(up, w).norm();
		const auto v = cross(w, u).norm();

		return Camera(
			from,
			from - w,
			2.0 * half_width * u,
			2.0 * half_height * v);
	}
};