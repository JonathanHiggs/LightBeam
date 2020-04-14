#pragma once


#include "IHittable.hpp"
#include "IMaterial.hpp"


namespace LightBeam
{
	namespace Shapes
	{

		class XYRectangle : public Rendering::IHittable {
		private:
			std::shared_ptr<const Materials::IMaterial> _material;
			double _x0, _x1, _y0, _y1;
			double _k;

		public:
			XYRectangle(
				double x0,
				double x1,
				double y0,
				double y1,
				double k,
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