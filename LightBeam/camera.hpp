#pragma once


#include "ray.hpp"
#include "vec3.hpp"
#include "random.hpp"


class Camera {
private:
	Vec3 _origin;
	Vec3 _center;
	Vec3 _horizontal;
	Vec3 _vertical;

public:
	Camera()
		: Camera{ Vec3::zero, -Vec3::unit_z, Vec3::unit_x, Vec3::unit_y }
	{}

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

	Ray get_ray(double u, double v) {
		return Ray(_origin, _center + u * _horizontal + v * _vertical - _origin);
	}
};