#pragma once


#include "IHittable.hpp"


namespace LightBeam
{
	namespace Shapes
	{

		class YRotation : public Rendering::IHittable
		{
		private:
			std::shared_ptr<const Rendering::IHittable> _hittable;
			double _sin_theta, _cos_theta;
			bool _has_box;
			Rendering::AxisAlignedBoundingBox _bounding_box;

		public:
			YRotation(
				double angle,
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