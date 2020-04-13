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

			record = HitRecord(distance, point, normal, Vec2::zero, !inside, _material);

			return true;
		}

		bool Sphere::bounding_box(
			double begin_time,
			double end_time,
			AxisAlignedBoundingBox& bounding_box) const
		{
			bounding_box = AxisAlignedBoundingBox(
				_center - Vec3(_radius, _radius, _radius),
				_center + Vec3(_radius, _radius, _radius));
			return true;
		}
	}
}