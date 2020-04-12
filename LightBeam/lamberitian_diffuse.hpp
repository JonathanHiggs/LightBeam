#pragma once

#include "material.hpp"


class LambertianDiffuse : public IMaterial {
private:
	Color _albedo;

public:
	LambertianDiffuse(const Color& albedo)
		: _albedo{albedo}
	{}


	bool scatter(
		const Ray& ray,
		const HitRecord& hit_record,
		Color& attenuation,
		Ray& scattered
	) const {
		auto scatter_direction = hit_record.normal() + Vec3::random_unit_vector();
		scattered = Ray(hit_record.point(), scatter_direction);
		attenuation = _albedo;
		return true;
	}
};