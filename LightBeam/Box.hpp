#pragma once


#include "IHittable.hpp"
#include "IMaterial.hpp"
#include "HittableList.hpp"


namespace LightBeam
{
	namespace Shapes
	{

		class Box : public Rendering::IHittable
		{
		private:
			Math::Vec3 _min;
			Math::Vec3 _max;
			Rendering::HittableList _sides;

		public:
			Box(
				const Math::Vec3& p0,
				const Math::Vec3& p1,
				std::shared_ptr<const Materials::IMaterial> material);

			bool hit(
				const Rendering::Ray& ray,
				double min_distance,
				double max_distance,
				Rendering::HitRecord& record) const;

			bool bounding_box(
				double begin_time,
				double end_time,
				Rendering::AxisAlignedBoundingBox& bounding_box) const;
		};

	}
}