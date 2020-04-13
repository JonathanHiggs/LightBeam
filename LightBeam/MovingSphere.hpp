#pragma once

#include "IHittable.hpp"
#include "IMaterial.hpp"


namespace LightBeam
{
	namespace Shapes
	{
		class MovingSphere : public Rendering::IHittable {
		private:
			Math::Vec3 _center_t0;
			Math::Vec3 _center_t1;
			double _t0;
			double _t1;
			double _radius;
			std::shared_ptr<const Materials::IMaterial> _material;

		public:
			MovingSphere(
				const Math::Vec3& center_t0,
				const Math::Vec3& center_t1,
				double t0,
				double t1,
				double radius,
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

			Math::Vec3 center(double time) const;

			Math::Vec3 outward_normal(const Math::Vec3& p, double time) const;

			Math::Vec3 inward_normal(const Math::Vec3& p, double time) const;
		};
	}
}