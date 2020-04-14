#include "Sphere.hpp"


using namespace LightBeam::Math;
using namespace LightBeam::Rendering;


namespace LightBeam
{
	namespace Shapes
	{
		bool Sphere::hit(
			const Ray& ray,
			double min_distance,
			double max_distance,
			HitRecord& record) const
		{
			const auto oc = ray.origin() - _center;
			const auto a = Vec3::dot(ray.direction(), ray.direction());
			const auto half_b = Vec3::dot(oc, ray.direction());
			const auto c = Vec3::dot(oc, oc) - _radius * _radius;

			const auto discriminant = half_b * half_b - a * c;

			if (discriminant < 0)
				return false;

			const auto distance = (-half_b - std::sqrt(discriminant)) / a;

			if (distance < min_distance || distance > max_distance)
				return false;

			const auto point = ray.at(distance);
			auto normal = outward_normal(point);
			const auto inside = Vec3::dot(ray.direction(), normal) > 0.0;

			if (inside)
				normal = -normal;

			const auto uv = uv_from_point(point);

			record = HitRecord(distance, point, normal, uv, !inside, _material);

			return true;
		}

		bool Sphere::bounding_box(
			double begin_time,
			double end_time,
			AxisAlignedBoundingBox& bounding_box) const
		{
			auto abs_radius = std::abs(_radius);

			bounding_box = AxisAlignedBoundingBox(
				_center - Vec3(abs_radius, abs_radius, abs_radius),
				_center + Vec3(abs_radius, abs_radius, abs_radius));

			return true;
		}

		Vec3 Sphere::outward_normal(const Math::Vec3& p) const
		{
			return (p - _center).norm();
		}

		Vec3 Sphere::inward_normal(const Math::Vec3& p) const
		{
			return -outward_normal(p);
		}

		Vec2 Sphere::uv_from_point(const Math::Vec3& point) const
		{
			auto relative_point = (point - _center) / _radius;
			auto phi = std::atan2(relative_point.z(), relative_point.x());
			auto theta = std::asin(relative_point.y());

			return Math::Vec2(
				1.0 - (phi + M_PI) / (2 * M_PI),
				(theta + M_PI / 2) / M_PI);
		}
	}
}