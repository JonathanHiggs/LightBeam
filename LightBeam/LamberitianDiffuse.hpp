#pragma once

#include "IMaterial.hpp"


namespace LightBeam
{
	namespace Materials
	{
		class LambertianDiffuse : public IMaterial {
		private:
			Image::Color _albedo;

		public:
			LambertianDiffuse(const Image::Color& albedo)
				: _albedo{ albedo }
			{}


			bool scatter(
				const Rendering::Ray& ray,
				const Rendering::HitRecord& hit_record,
				Image::Color& attenuation,
				Rendering::Ray& scattered
			) const {
				auto scatter_direction = hit_record.normal() + Math::Vec3::random_unit_vector();
				scattered = Rendering::Ray(hit_record.point(), scatter_direction);
				attenuation = _albedo;
				return true;
			}
		};
	}
}