#pragma once


#include "IMaterial.hpp"
#include "ITexture.hpp"


namespace LightBeam
{
	namespace Materials
	{

		class DiffuseLight : public IMaterial {
		private:
			std::shared_ptr<const Textures::ITexture> _emit;

		public:
			DiffuseLight(const Image::Color& color);

			DiffuseLight(const Image::Color& color, double intensity);

			DiffuseLight(std::shared_ptr<const Textures::ITexture> emit);

			bool scatter(
				const Rendering::Ray& ray,
				const Rendering::HitRecord& hit_record,
				Image::Color& attenuation,
				Rendering::Ray& scattered) const;

			Image::Color emitted(const Math::Vec2& uv, const Math::Vec3& point) const;
		};

	}
}