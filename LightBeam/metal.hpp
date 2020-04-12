#pragma once


#include "material.hpp"


class Metal : public IMaterial {
private:
	Color _albedo;
	double _fuzz;

public:
	Metal(const Color& albedo, double fuzz)
		: _albedo{ albedo }
		, _fuzz{ clamp(fuzz, 0.0, 1.0) }
	{}


	bool scatter(
		const Ray& ray,
		const HitRecord& hit_record,
		Color& attenuation,
		Ray& scattered
	) const {
		auto reflected = Vec3::reflect(ray.direction().norm(), hit_record.normal());
		scattered = Ray(hit_record.point(), reflected + _fuzz * Vec3::random_in_unit_sphere());
		attenuation = _albedo;
		return (dot(scattered.direction(), hit_record.normal()) > 0.0);
	}
};