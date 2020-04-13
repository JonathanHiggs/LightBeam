#pragma once


#include "IMaterial.hpp"
#include "ITexture.hpp"
#include "ConstantTexture.hpp"


namespace LightBeam
{
	namespace Materials
	{
		class LambertianDiffuse : public IMaterial {
		private:
			std::shared_ptr<const Textures::ITexture> _albedo;

		public:
			LambertianDiffuse(const Image::Color& albedo)
				: _albedo{ std::make_shared<const Textures::ConstantTexture>(albedo) }
			{}

			LambertianDiffuse(std::shared_ptr<const Textures::ITexture> albedo)
				: _albedo{ std::move(albedo) }
			{}

			bool scatter(
				const Rendering::Ray& ray,
				const Rendering::HitRecord& hit_record,
				Image::Color& attenuation,
				Rendering::Ray& scattered
			) const {
				auto scatter_direction = hit_record.normal() + Math::Vec3::random_unit_vector();
				scattered = Rendering::Ray(hit_record.point(), scatter_direction, ray.time());
				attenuation = _albedo->value(hit_record.uv(), hit_record.point());
				return true;
			}
		};
	}
}