#pragma once


#include "Bitmap.hpp"
#include "ITexture.hpp"


namespace LightBeam
{
	namespace Textures
	{

		class ImageTexture : public ITexture {
		private:
			const std::shared_ptr<const Image::Bitmap> _bitmap;

		public:
			ImageTexture(std::shared_ptr<const Image::Bitmap> image)
				: _bitmap{ std::move(image) }
			{}

			Image::Color value(const Math::Vec2& uv, const Math::Vec3& point) const
			{
				auto i = static_cast<int>(uv.x() * _bitmap->width());
				auto j = static_cast<int>((1 - uv.y()) * _bitmap->height());

				if (i < 0)
					i = 0;

				if (j < 0)
					j = 0;

				auto i2 = static_cast<unsigned int>(i);
				auto j2 = static_cast<unsigned int>(j);

				if (i2 > _bitmap->width() - 1)
					i2 = _bitmap->width() - 1;

				if (j2 > _bitmap->height() - 1)
					j2 = _bitmap->height() - 1;

				return Image::Color(_bitmap->get_pixel(i2, j2));
			}
		};

	}
}