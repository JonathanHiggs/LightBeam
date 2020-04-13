#include "MovingSphere.hpp"


using namespace LightBeam::Math;
using namespace LightBeam::Materials;
using namespace LightBeam::Rendering;


namespace LightBeam
{
	namespace Shapes
	{

		MovingSphere::MovingSphere(
			const Vec3& center_t0,
			const Vec3& center_t1,
			double t0,
			double t1,
			double radius,
			std::shared_ptr<const IMaterial> material
		)
			: _center_t0{ center_t0 }
			, _center_t1{ center_t1 }
			, _t0{ t0 }
			, _t1{ t1 }
			, _radius{ radius }
			, _material{ std::move(material) }
		{}


		bool MovingSphere::hit(
			const Ray& ray,
			double min_distance,
			double max_distance,
			HitRecord& record) const
		{
			const auto oc = ray.origin() - center(ray.time());
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
			auto normal = outward_normal(point, ray.time());
			const auto inside = Math::Vec3::dot(ray.direction(), normal) > 0.0;

			if (inside)
				normal = -normal;

			record = HitRecord(distance, point, normal, !inside, _material);

			return true;
		}

		bool MovingSphere::bounding_box(
			double begin_time,
			double end_time,
			AxisAlignedBoundingBox& bounding_box) const
		{
			auto box0 = AxisAlignedBoundingBox(
				center(begin_time) - Vec3(_radius, _radius, _radius),
				center(begin_time) + Vec3(_radius, _radius, _radius));

			auto box1 = AxisAlignedBoundingBox(
				center(end_time) - Vec3(_radius, _radius, _radius),
				center(end_time) + Vec3(_radius, _radius, _radius));

			bounding_box = AxisAlignedBoundingBox::surrounding_box(box0, box1);
			return true;
		}


		Vec3 MovingSphere::center(double time) const {
			return Vec3::interpolate(_center_t0, _center_t1, (time - _t0) / (_t1 - _t0));
		}

		Vec3 MovingSphere::outward_normal(const Vec3& p, double time) const {
			return (p - center(time)).norm();
		}

		Vec3 MovingSphere::inward_normal(const Vec3& p, double time) const {
			return -outward_normal(p, time);
		}
	}
}