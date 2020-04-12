#pragma once

#include "hit_record.hpp"


class IHittable {
public:
	virtual bool hit(
		const Ray& ray,
		double min_distance,
		double max_distance,
		HitRecord& record) const = 0;
};