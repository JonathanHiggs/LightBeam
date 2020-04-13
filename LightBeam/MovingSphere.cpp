#include "MovingSphere.hpp"


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
			IMaterialCPtr material
		)
			: _center_t0{ center_t0 }
			, _center_t1{ center_t1 }
			, _t0{ t0 }
			, _t1{ t1 }
			, _radius{ radius }
			, _material{ std::move(material) }
		{}


		bool MovingSphere::hit(
			const Rendering::Ray& ray,
			double min_distance,
			double max_distance,
			Rendering::HitRecord& record) const
		{
			const auto oc = ray.origin() - center(ray.time());
			const auto a = Math::Vec3::dot(ray.direction(), ray.direction());
			const auto half_b = Math::Vec3::dot(oc, ray.direction());
			const auto c = Math::Vec3::dot(oc, oc) - _radius * _radius;

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

			record = Rendering::HitRecord(distance, point, normal, !inside, _material);

			return true;
		}


		MovingSphere::Vec3 MovingSphere::center(double time) const {
			return Vec3::interpolate(_center_t0, _center_t1, (time - _t0) / (_t1 - _t0));
		}

		MovingSphere::Vec3 MovingSphere::outward_normal(const Math::Vec3& p, double time) const {
			return (p - center(time)).norm();
		}

		MovingSphere::Vec3 MovingSphere::inward_normal(const Math::Vec3& p, double time) const {
			return -outward_normal(p, time);
		}
	}
}