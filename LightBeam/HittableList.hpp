#pragma once

#include <memory>
#include <vector>

#include "IHittable.hpp"


class HittableList : public IHittable {
private:
	std::vector<std::shared_ptr<IHittable>> _hittables;

public:
	HittableList()
		: _hittables{}
	{}

	void add(const std::shared_ptr<IHittable> & hittable)
	{
		_hittables.emplace_back(hittable);
	}

	bool hit(
		const Ray& ray,
		double min_distance,
		double max_distance,
		HitRecord& record) const;
};