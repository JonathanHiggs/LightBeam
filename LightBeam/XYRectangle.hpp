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
			double _z;

		public:
			XYRectangle(
				double x0,
				double x1,
				double y0,
				double y1,
				double z,
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

			double pdf_value(
				const Math::Vec3& origin,
				const Math::Vec3& direction) const;

			Math::Vec3 random_from_source(const Math::Vec3& source) const;
		};

	}
}