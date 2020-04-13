#include "HittableList.hpp"


bool HittableList::hit(
	const Ray& ray,
	double min_distance,
	double max_distance,
	HitRecord& record) const
{
	bool any_hits = false;
	HitRecord temp;

	for (const auto & hitable : _hittables)
	{
		if (!hitable->hit(ray, min_distance, max_distance, temp))
			continue;

		if (any_hits && record.distance() < temp.distance())
			continue;

		any_hits = true;
		record = temp;
	}

	return any_hits;
}