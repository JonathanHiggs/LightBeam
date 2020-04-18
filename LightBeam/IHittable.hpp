#pragma once

#include "AxisAlignedBoundingBox.hpp"
#include "HitRecord.hpp"
#include "memory.hpp"


namespace LightBeam
{
	namespace Rendering
	{
		// ToDo: move to Shapes namespace
		class IHittable {
		public:
			virtual bool hit(
				const Ray& ray,
				double min_distance,
				double max_distance,
				HitRecord& record) const = 0;

			virtual bool bounding_box(
				double begin_time,
				double end_time,
				AxisAlignedBoundingBox& bounding_box) const = 0;
		};

		DECLARE_STD_PTR(IHittable)

	}
}