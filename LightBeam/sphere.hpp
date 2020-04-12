#pragma once

#include <memory>

#include "hittable.hpp"
#include "material.hpp"


class Sphere : public IHittable {
private:
	Vec3 _center;
	double _radius;
	std::shared_ptr<const IMaterial> _material;

public:
	Sphere(const Vec3& origin, double radius, std::shared_ptr<const IMaterial> material)
		: _center{origin}
		, _radius{radius}
		, _material{std::move(material)}
	{}

	const Vec3& center() const noexcept { return _center; }
	double radius() const noexcept { return _radius; }
	const std::shared_ptr<const IMaterial> material() const noexcept { return _material; }

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