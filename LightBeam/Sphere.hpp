#pragma once

#include <memory>

#include "IHittable.hpp"
#include "IMaterial.hpp"


namespace LightBeam
{
	namespace Shapes
	{
		class Sphere : public Rendering::IHittable {
		private:
			Math::Vec3 _center;
			double _radius;
			std::shared_ptr<const Materials::IMaterial> _material;

		public:
			Sphere(
				const Math::Vec3& origin,
				double radius,
				std::shared_ptr<const Materials::IMaterial> material
			)
				: _center{ origin }
				, _radius{ radius }
				, _material{ std::move(material) }
			{}

			const Math::Vec3& center() const noexcept { return _center; }
			double radius() const noexcept { return _radius; }

			const std::shared_ptr<const Materials::IMaterial> material() const noexcept {
				return _material;
			}

			bool hit(
				const Rendering::Ray& ray,
				double min_distance,
				double max_distance,
				Rendering::HitRecord& record) const;

			bool bounding_box(
				double begin_time,
				double end_time,
				Rendering::AxisAlignedBoundingBox& bounding_box) const;

			Math::Vec3 outward_normal(const Math::Vec3& p) const;

			Math::Vec3 inward_normal(const Math::Vec3& p) const;

			Math::Vec2 uv_from_point(const Math::Vec3& point) const;
		};
	}
}