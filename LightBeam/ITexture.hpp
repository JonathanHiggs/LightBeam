#pragma once


#include "Color.hpp"
#include "Vec2.hpp"
#include "memory.hpp"


namespace LightBeam
{
	namespace Textures
	{

		class ITexture {
		public:
			virtual Image::Color value(
				const Math::Vec2& uv,
				const Math::Vec3& point) const = 0;
		};

		DECLARE_STD_PTR(ITexture)

	}
}