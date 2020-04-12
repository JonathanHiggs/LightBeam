#pragma once


#include "ray.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "random.hpp"
#include "utils.hpp"


class Camera {
private:
	Vec3 _origin;
	Vec3 _center;
	Vec3 _horizontal;
	Vec3 _vertical;
	Vec3 _u, _v, _w;
	double _lens_radius;

public:
	Camera(
		const Vec3& origin,
		const Vec3& center,
		const Vec3& horizontal,
		const Vec3& vertical,
		const Vec3& u,
		const Vec3& v,
		const Vec3& w,
		double lens_radius)
		: _origin{origin}
		, _center{center}
		, _horizontal{horizontal}
		, _vertical{vertical}
		, _u{ u }
		, _v{ v }
		, _w{ w }
		, _lens_radius{ lens_radius }
	{ }

	static Camera from_vfov(
		const Vec3& from,
		const Vec3& at,
		const Vec3& up,
		double vfov,
		double aspect_ratio,
		double aperture,
		double focal_distance)
	{
		const auto theta = degrees_to_radians(vfov);
		const auto half_height = std::tan(theta / 2.0);
		const auto half_width = aspect_ratio * half_height;

		return _from(from, at, up, half_width, half_height, aperture, focal_distance);
	}

	static Camera from_hfov(
		const Vec3& from,
		const Vec3& at,
		const Vec3& up,
		double hfov,
		double aspect_ratio,
		double aperture,
		double focal_distance)
	{
		auto theta = degrees_to_radians(hfov);
		auto half_width = std::tan(theta / 2.0);
		auto half_height = half_width / aspect_ratio;

		return _from(from, at, up, half_width, half_height, aperture, focal_distance);
	}


	Ray get_ray(double u, double v) {
		const auto rd = _lens_radius * Vec2::random_in_unit_disk();
		const auto offset = _u * rd.x() + _v * rd.y();
		return Ray(
			_origin + offset,
			_center + u * _horizontal + v * _vertical - _origin);
	}

private:
	static Camera _from(
		const Vec3& from,
		const Vec3& at,
		const Vec3& up,
		double half_width,
		double half_height,
		double aperture,
		double focal_distance)
	{
		// get the orthonormal basis
		const auto w = (from - at).norm();
		const auto u = Vec3::cross(up, w).norm();
		const auto v = Vec3::cross(w, u).norm();

		return Camera(
			from,
			from - w,
			2.0 * half_width * focal_distance * u,
			2.0 * half_height * focal_distance * v,
			u,
			v,
			w,
			aperture / 2.0);
	}
};