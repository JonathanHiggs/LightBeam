#pragma once

#include <memory>

#include "Ray.hpp"


class IMaterial;


class HitRecord {
private:
	double _distance;
	Vec3 _point;
	Vec3 _normal;
	bool _front_face;
	std::shared_ptr<const IMaterial> _material;

public:
	HitRecord()
		: _distance(std::nan("1"))
		, _point{ Vec3::nan }
		, _normal(Vec3::nan)
		, _front_face{ false }
	{}

	HitRecord(double distance, const Vec3& point, const Vec3& normal, bool front_face)
		: _distance{ distance }
		, _point{ point }
		, _normal{ normal }
		, _front_face{ front_face }
	{}

	HitRecord(
		double distance,
		const Vec3& point,
		const Vec3& normal,
		bool front_face,
		std::shared_ptr<const IMaterial> material
	)
		: _distance{ distance }
		, _point{ point }
		, _normal{ normal }
		, _front_face{ front_face }
		, _material{ std::move(material) }
	{}

	double distance() const noexcept { return _distance; }
	const Vec3& point() const noexcept { return _point; }
	const Vec3& normal() const noexcept { return _normal; }
	bool front_face() const noexcept { return _front_face; }
	const std::shared_ptr<const IMaterial> meterial() const noexcept { return _material; }
};
