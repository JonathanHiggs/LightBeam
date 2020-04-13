#pragma once


#include "ITexture.hpp"


namespace LightBeam
{
	namespace Textures
	{

		class ConstantTexture : public ITexture {
		private:
			Image::Color _color;

		public:
			ConstantTexture(Image::Color color)
				: _color{ color }
			{}

			Image::Color value(const Math::Vec2& uv, const Math::Vec3& point) const {
				return _color;
			}
		};

	}
}