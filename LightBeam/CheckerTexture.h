#pragma once


#include "ITexture.hpp"
#include "ConstantTexture.hpp"


namespace LightBeam
{
	namespace Textures
	{

		class CheckersTexture : public ITexture {
		private:
			std::shared_ptr<const ITexture> _odd;
			std::shared_ptr<const ITexture> _even;

		public:
			CheckersTexture(
				std::shared_ptr<const ITexture> odd,
				std::shared_ptr<const ITexture> even
			)
				: _odd{ odd }
				, _even{ even }
			{}

			CheckersTexture(
				const Image::Color& odd,
				const Image::Color& even
			)
				: CheckersTexture(
					std::make_shared<const ConstantTexture>(odd),
					std::make_shared<const ConstantTexture>(even))
			{}

			Image::Color value(const Math::Vec2& uv, const Math::Vec3& point) const
			{
				auto sines = std::sin(10 * point.x())
					* std::sin(10 * point.y())
					* std::sin(10 * point.z());

				return sines < 0.0
					? _odd->value(uv, point)
					: _even->value(uv, point);
			}
		};

	}
}