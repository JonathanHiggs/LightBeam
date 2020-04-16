#include "HittableList.hpp"


namespace LightBeam
{
	namespace Rendering
	{
		bool HittableList::hit(
			const Ray& ray,
			double min_distance,
			double max_distance,
			HitRecord& record) const
		{
			bool any_hits = false;
			HitRecord temp;

			for (const auto& hittable : _hittables)
			{
				if (!hittable->hit(ray, min_distance, max_distance, temp))
					continue;

				if (any_hits && record.distance() < temp.distance())
					continue;

				any_hits = true;
				record = temp;
			}

			return any_hits;
		}

		bool HittableList::bounding_box(
			double begin_time,
			double end_time,
			AxisAlignedBoundingBox& bounding_box) const
		{
			if (_hittables.empty())
				return false;

			AxisAlignedBoundingBox temp_box;
			bool first_box = true;

			for (const auto& hittable : _hittables) {
				if (!hittable->bounding_box(begin_time, end_time, temp_box))
					return false;

				bounding_box = first_box
					? temp_box
					: AxisAlignedBoundingBox::surrounding_box(bounding_box, temp_box);
				first_box = false;
			}

			return true;
		}
	}
}