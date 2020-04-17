#pragma once


#include "IHittable.hpp"



namespace LightBeam
{
	namespace Shapes
	{

		class Translate : public Rendering::IHittable
		{
		private:
			std::shared_ptr<const Rendering::IHittable> _hittable;
			Math::Vec3 _offset;

		public:
			Translate(
				const Math::Vec3& offset,
				std::shared_ptr<const Rendering::IHittable> hittable);

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
