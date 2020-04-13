#pragma once


#include "IMaterial.hpp"


namespace LightBeam
{
	namespace Materials
	{
		class Metal : public IMaterial {
		private:
			Image::Color _albedo;
			double _fuzz;

		public:
			Metal(const Image::Color& albedo, double fuzz)
				: _albedo{ albedo }
				, _fuzz{ Util::clamp(fuzz, 0.0, 1.0) }
			{}

			bool scatter(
				const Rendering::Ray& ray,
				const Rendering::HitRecord& hit_record,
				Image::Color& attenuation,
				Rendering::Ray& scattered
			) const {
				auto reflected = Math::Vec3::reflect(ray.direction().norm(), hit_record.normal());

				scattered = Rendering::Ray(
					hit_record.point(),
					reflected + _fuzz * Math::Vec3::random_in_unit_sphere(),
					ray.time());

				attenuation = _albedo;
				return (Math::Vec3::dot(scattered.direction(), hit_record.normal()) > 0.0);
			}
		};
	}
}