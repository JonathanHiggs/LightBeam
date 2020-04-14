#include "XYRectangle.hpp"


using namespace LightBeam::Math;
using namespace LightBeam::Materials;
using namespace LightBeam::Rendering;


namespace LightBeam
{
	namespace Shapes
	{

		XYRectangle::XYRectangle(
			double x0,
			double x1,
			double y0,
			double y1,
			double k,
			std::shared_ptr<const IMaterial> material
		)
			: _x0{ x0 }
			, _x1{ x1 }
			, _y0{ y0 }
			, _y1{ y1 }
			, _k{ k }
			, _material{ std::move(material) }
		{}

		bool XYRectangle::hit(
			const Ray& ray,
			double min_distance,
			double max_distance,
			HitRecord& record) const
		{
			auto distance = (_k - ray.origin().z()) / ray.direction().z();

			if (distance < min_distance || distance > max_distance)
				return false;

			auto x = ray.origin().x() + distance * ray.direction().x();
			auto y = ray.origin().y() + distance * ray.direction().y();

			if (x < _x0 || x > _x1 || y < _y0 || y > _y1)
				return false;

			auto point = Vec3(x, y, _k);
			auto outward_normal = Vec3::unit_z;
			auto uv = Vec2(
				(x - _x0) / (_x1 - _x0),
				(y - _y0) / (_y1 - _y0));

			auto front_face = Vec3::dot(outward_normal, ray.direction());

			record = HitRecord(
				distance,
				point,
				front_face ? outward_normal : -outward_normal,
				uv,
				front_face,
				_material);

			return true;
		}

		bool XYRectangle::bounding_box(
			double begin_time,
			double end_time,
			AxisAlignedBoundingBox& bounding_box) const
		{
			bounding_box = AxisAlignedBoundingBox(
				Vec3(_x0, _y0, _k - 1e-4),
				Vec3(_x1, _y1, _k + 1e-4));

			return true;
		}

	}
}