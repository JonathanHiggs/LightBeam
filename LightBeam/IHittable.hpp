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

			virtual double pdf_value(
				const Math::Vec3& origin,
				const Math::Vec3& direction) const
			{
				return 0.0;
			}

			virtual Math::Vec3 random_from_source(const Math::Vec3& source) const
			{
				return Math::Vec3::zero;
			}
		};

		DECLARE_STD_PTR(IHittable)

	}
}