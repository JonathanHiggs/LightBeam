#include "XZRectangle.hpp"
#include "utils.hpp"
#include "Constants.hpp"


using namespace LightBeam::Math;
using namespace LightBeam::Materials;
using namespace LightBeam::Rendering;
using namespace LightBeam::Util;


namespace LightBeam
{
	namespace Shapes
	{

		XZRectangle::XZRectangle(
			double x0,
			double x1,
			double z0,
			double z1,
			double y,
			std::shared_ptr<const IMaterial> material,
			bool flip_normal
		)
			: _x0{ ffmin(x0, x1) }
			, _x1{ ffmax(x0, x1) }
			, _z0{ ffmin(z0, z1) }
			, _z1{ ffmax(z0, z1) }
			, _y{ y }
			, _material{ std::move(material) }
			, _flip_normal{ flip_normal }
		{}

		bool XZRectangle::hit(
			const Ray& ray,
			double min_distance,
			double max_distance,
			HitRecord& record) const
		{
			auto distance = (_y - ray.origin().y()) / ray.direction().y();

			if (distance < min_distance || distance > max_distance)
				return false;

			auto x = ray.origin().x() + distance * ray.direction().x();
			auto z = ray.origin().z() + distance * ray.direction().z();

			if (x < _x0 || x > _x1 || z < _z0 || z > _z1)
				return false;

			auto point = Vec3(x, _y, z);
			auto outward_normal = _flip_normal ? -Vec3::unit_y : Vec3::unit_y;
			auto uv = Vec2(
				(x - _x0) / (_x1 - _x0),
				(z - _z0) / (_z1 - _z0));

			auto front_face = Vec3::dot(ray.direction(), outward_normal) < 0.0;
			auto normal = front_face ? outward_normal : -outward_normal;

			record = HitRecord(distance, point, normal, uv, front_face, _material);

			return true;
		}

		bool XZRectangle::bounding_box(
			double begin_time,
			double end_time,
			AxisAlignedBoundingBox& bounding_box) const
		{
			bounding_box = AxisAlignedBoundingBox(
				Vec3(_x0, _y - 1e-4, _z0),
				Vec3(_x1, _y + 1e-4, _z1));

			return true;
		}

		double XZRectangle::pdf_value(
			const Vec3& origin,
			const Vec3& direction) const
		{
			HitRecord hit_record;
			auto ray = Ray(origin, direction);

			if (!hit(ray, 1e-8, infinity, hit_record))
				return 0;

			auto area = (_x1 - _x0) * (_z1 - _z0);

			auto distance_squared =
				hit_record.distance()
				* hit_record.distance()
				* direction.length_squared();

			auto cosine =
				std::abs(Vec3::dot(direction, hit_record.normal()) / direction.length());

			return distance_squared / (cosine * area);
		}

		Vec3 XZRectangle::random_from_source(const Vec3& source) const
		{
			auto random_point = Vec3(
				random_double(_x0, _x1),
				_y,
				random_double(_z0, _z1));

			return random_point - source;
		}

	}
}