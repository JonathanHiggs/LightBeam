#pragma once


#include "Color.hpp"
#include "IHittable.hpp"
#include "Ray.hpp"


namespace LightBeam
{
	namespace Materials
	{
		class IMaterial {
		public:
			virtual bool scatter(
				const Rendering::Ray& ray,
				const Rendering::HitRecord& hit_record,
				Image::Color& attenuation,
				Rendering::Ray& scattered) const = 0;

			virtual Image::Color emitted(
				const Math::Vec2& uv,
				const Math::Vec3& point) const
			{
				return Math::Vec3::zero;
			}
		};
	}
}