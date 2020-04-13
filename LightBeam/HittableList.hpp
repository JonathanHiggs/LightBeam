#pragma once

#include <memory>
#include <vector>

#include "IHittable.hpp"


namespace LightBeam
{
	namespace Rendering
	{
		class HittableList : public IHittable {
		private:
			std::vector<std::shared_ptr<const IHittable>> _hittables;

		public:
			HittableList()
				: _hittables{}
			{}

			HittableList(std::vector<std::shared_ptr<const IHittable>> hittables)
				: _hittables{ hittables }
			{}

			const std::vector<std::shared_ptr<const IHittable>>& hittables() const noexcept {
				return _hittables;
			}

			bool hit(
				const Ray& ray,
				double min_distance,
				double max_distance,
				HitRecord& record) const;

			bool bounding_box(
				double begin_time,
				double end_time,
				AxisAlignedBoundingBox& bounding_box) const;
		};
	}
}