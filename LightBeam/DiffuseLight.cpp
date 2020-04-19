#include "DiffuseLight.hpp"
#include "ConstantTexture.hpp"


using namespace LightBeam;
using namespace LightBeam::Image;
using namespace LightBeam::Math;
using namespace LightBeam::Rendering;
using namespace LightBeam::Textures;


namespace LightBeam
{
	namespace Materials
	{

		DiffuseLight::DiffuseLight(const Image::Color& color)
			: DiffuseLight(std::make_shared<const ConstantTexture>(color))
		{}

		DiffuseLight::DiffuseLight(const Image::Color& color, double intensity)
			: DiffuseLight(color* intensity)
		{}

		DiffuseLight::DiffuseLight(std::shared_ptr<const ITexture> emit)
			: _emit{ std::move(emit) }
		{}

		bool DiffuseLight::scatter(
			const Ray& ray,
			const HitRecord& hit_record,
			Color& attenuation,
			Ray& scattered,
			double& pdf) const
		{
			return false;
		}

		Color DiffuseLight::emitted(const Vec2& uv, const Vec3& point) const
		{
			return _emit->value(uv, point);
		}

	}
}