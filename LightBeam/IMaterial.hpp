#pragma once


#include "Color.hpp"
#include "IHittable.hpp"
#include "Ray.hpp"


class IMaterial {
public:
	virtual bool scatter(
		const Ray& ray,
		const HitRecord& hit_record,
		Color& attenuation,
		Ray& scattered
	) const = 0;
};