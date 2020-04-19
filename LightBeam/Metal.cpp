#include "Metal.hpp"


using namespace LightBeam::Image;
using namespace LightBeam::Math;
using namespace LightBeam::Rendering;
using namespace LightBeam::Util;


namespace LightBeam
{
	namespace Materials
	{

		Metal::Metal(const Color& albedo, double fuzz)
			: _albedo{ albedo }
			, _fuzz{ clamp(fuzz, 0.0, 1.0) }
		{}

		bool Metal::scatter(
			const Ray& ray,
			const HitRecord& hit_record,
			Color& albedo,
			Ray& scattered,
			double& pdf
		) const {
			auto reflected = Vec3::reflect(ray.direction().norm(), hit_record.normal());

			scattered = Ray(
				hit_record.point(),
				reflected + _fuzz * Vec3::random_in_unit_sphere(),
				ray.time());

			albedo = _albedo;
			return (Vec3::dot(scattered.direction(), hit_record.normal()) > 0.0);
		}

		/*double Metal::scattering_pdf(
			const Ray& ray,
			const HitRecord& hit_record,
			Ray& scattered
		) const {

		}*/

	}
}