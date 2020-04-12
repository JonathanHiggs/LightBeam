#pragma once

#include "hittable.hpp"


class Sphere : public IHittable {
private:
	Vec3 _center;
	double _radius;

public:
	Sphere(const Vec3& origin, double radius)
		: _center{origin}
		, _radius{radius}
	{}

	const Vec3& center() const noexcept { return _center; }
	double radius() const noexcept { return _radius; }

	bool hit(
		const Ray& ray,
		double min_distance,
		double max_distance,
		HitRecord& record) const;

	Vec3 outward_normal(const Vec3& p) const {
		return (p - _center).norm();
	}

	Vec3 inward_normal(const Vec3& p) const { return -outward_normal(p); }
};