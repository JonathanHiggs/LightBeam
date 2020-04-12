#pragma once


#include "color.hpp"
#include "ray.hpp"
#include "hittable.hpp"


class IMaterial {
public:
	virtual bool scatter(
		const Ray& ray,
		const HitRecord& hit_record,
		Color& attenuation,
		Ray& scattered
	) const = 0;
};