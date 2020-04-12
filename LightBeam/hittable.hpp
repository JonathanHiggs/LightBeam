#pragma once

#include "ray.hpp"


class HitRecord {
private:
	double _distance;
	Vec3 _point;
	Vec3 _normal;
	bool _front_face;

public:
	HitRecord()
		: _distance(std::nan("1"))
		, _point{Vec3::nan}
		, _normal(Vec3::nan)
		, _front_face{false}
	{}

	HitRecord(double distance, const Vec3& point, const Vec3& normal, bool front_face)
		: _distance{distance}
		, _point{point}
		, _normal{normal}
		, _front_face{front_face}
	{}

	double distance() const noexcept { return _distance; }
	const Vec3& point() const noexcept { return _point; }
	const Vec3& normal() const noexcept { return _normal; }
	bool front_face() const noexcept { return _front_face; }
};


class IHittable {
public:
	virtual bool hit(
		const Ray& ray,
		double min_distance,
		double max_distance,
		HitRecord& record) const = 0;
};