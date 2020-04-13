#pragma once

#include "IHittable.hpp"
#include "IMaterial.hpp"


namespace LightBeam
{
	namespace Shapes
	{
		class MovingSphere : public Rendering::IHittable {
		public:
			typedef Math::Vec3 Vec3;
			typedef std::shared_ptr<const Materials::IMaterial> IMaterialCPtr;

		private:
			Vec3 _center_t0;
			Vec3 _center_t1;
			double _t0;
			double _t1;
			double _radius;
			IMaterialCPtr _material;

		public:
			MovingSphere(
				const Vec3& center_t0,
				const Vec3& center_t1,
				double t0,
				double t1,
				double radius,
				IMaterialCPtr material);

			bool hit(
				const Rendering::Ray& ray,
				double min_distance,
				double max_distance,
				Rendering::HitRecord& record) const;

			Vec3 center(double time) const;

			Vec3 outward_normal(const Math::Vec3& p, double time) const;

			Vec3 inward_normal(const Math::Vec3& p, double time) const;
		};
	}
}