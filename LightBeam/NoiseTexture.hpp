#pragma once


#include "ITexture.hpp"
#include "Perlin.hpp"


namespace LightBeam
{
	namespace Textures
	{

		class NoiseTexture : public ITexture {
		private:
			Noise::Perlin _noise;
			double _scale;

		public:
			NoiseTexture(Noise::Perlin perlin, double scale)
				: _noise{ perlin }
				, _scale{ scale }
			{}

			Image::Color value(const Math::Vec2& uv, const Math::Vec3& point) const {
				return Image::Color::WHITE
					* 0.5
					* (1.0 + std::sin(10.0 *  _noise.turb(point)));
			}
		};

	}
}