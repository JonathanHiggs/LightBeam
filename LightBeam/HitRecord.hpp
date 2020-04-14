#pragma once

#include <memory>

#include "Ray.hpp"
#include "Vec2.hpp"


namespace LightBeam
{

	namespace Materials
	{
		class IMaterial;
	}

	namespace Rendering
	{
		class HitRecord {
		private:
			double _distance;
			Math::Vec3 _point;
			Math::Vec3 _normal;
			Math::Vec2 _uv;
			bool _front_face;
			std::shared_ptr<const Materials::IMaterial> _material;

		public:
			HitRecord()
				: _distance(std::nan("1"))
				, _point{ Math::Vec3::nan }
				, _normal(Math::Vec3::nan)
				, _uv{ Math::Vec2::nan }
				, _front_face{ false }
				, _material{ nullptr }
			{}

			//HitRecord(
			//	double distance,
			//	const Math::Vec3& point,
			//	const Math::Vec3& normal,
			//	const Math::Vec2& uv,
			//	bool front_face
			//)
			//	: _distance{ distance }
			//	, _point{ point }
			//	, _normal{ normal }
			//	, _uv{ uv }
			//	, _front_face{ front_face }
			//{}

			HitRecord(
				double distance,
				const Math::Vec3& point,
				const Math::Vec3& normal,
				const Math::Vec2& uv,
				bool front_face,
				std::shared_ptr<const Materials::IMaterial> material
			)
				: _distance{ distance }
				, _point{ point }
				, _normal{ normal }
				, _uv{ uv }
				, _front_face{ front_face }
				, _material{ std::move(material) }
			{}

			double distance() const noexcept { return _distance; }
			const Math::Vec3& point() const noexcept { return _point; }
			const Math::Vec3& normal() const noexcept { return _normal; }
			const Math::Vec2& uv() const noexcept { return _uv; }
			bool front_face() const noexcept { return _front_face; }

			const std::shared_ptr<const Materials::IMaterial> meterial() const noexcept {
				return _material;
			}
		};
	}
}