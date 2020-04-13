#pragma once

#include "Vec3.hpp"


class Ray {
private:
	Vec3 _origin;
	Vec3 _direction;


public:
	Ray()
		: _origin{Vec3::nan}
		, _direction{Vec3::nan}
	{}

	Ray(const Vec3 & origin, const Vec3 & direction)
		: _origin{origin}
		, _direction{direction}
	{}


	const Vec3& origin() const noexcept { return _origin; }
	const Vec3& direction() const noexcept { return _direction; }


	Vec3 at(double t) const {
		return _origin + t * _direction;
	}
};