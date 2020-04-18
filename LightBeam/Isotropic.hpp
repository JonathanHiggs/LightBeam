#pragma once


#include "IMaterial.hpp"
#include "ITexture.hpp"


namespace LightBeam
{
	namespace Materials
	{

		class Isotropic : public IMaterial
		{
		public:
			Textures::ITextureCPtr albedo;

			Isotropic(Textures::ITextureCPtr albedo);

			bool scatter(
				const Rendering::Ray& ray,
				const Rendering::HitRecord& hit_record,
				Image::Color& attenuation,
				Rendering::Ray& scattered) const;
		};

	}
}
