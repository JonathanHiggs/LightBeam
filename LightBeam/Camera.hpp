#pragma once


#include "Ray.hpp"
#include "Random.hpp"
#include "Utils.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"


namespace LightBeam
{
	namespace Scene
	{
		class Camera {
		private:
			Math::Vec3 _origin;
			Math::Vec3 _center;
			Math::Vec3 _horizontal;
			Math::Vec3 _vertical;
			Math::Vec3 _u, _v, _w;
			double _lens_radius;

		public:
			Camera(
				const Math::Vec3& origin,
				const Math::Vec3& center,
				const Math::Vec3& horizontal,
				const Math::Vec3& vertical,
				const Math::Vec3& u,
				const Math::Vec3& v,
				const Math::Vec3& w,
				double lens_radius)
				: _origin{ origin }
				, _center{ center }
				, _horizontal{ horizontal }
				, _vertical{ vertical }
				, _u{ u }
				, _v{ v }
				, _w{ w }
				, _lens_radius{ lens_radius }
			{ }

			static Camera from_vfov(
				const Math::Vec3& from,
				const Math::Vec3& at,
				const Math::Vec3& up,
				double vfov,
				double aspect_ratio,
				double aperture,
				double focal_distance)
			{
				const auto theta = Util::degrees_to_radians(vfov);
				const auto half_height = std::tan(theta / 2.0);
				const auto half_width = aspect_ratio * half_height;

				return _from(from, at, up, half_width, half_height, aperture, focal_distance);
			}

			static Camera from_hfov(
				const Math::Vec3& from,
				const Math::Vec3& at,
				const Math::Vec3& up,
				double hfov,
				double aspect_ratio,
				double aperture,
				double focal_distance)
			{
				auto theta = Util::degrees_to_radians(hfov);
				auto half_width = std::tan(theta / 2.0);
				auto half_height = half_width / aspect_ratio;

				return _from(from, at, up, half_width, half_height, aperture, focal_distance);
			}


			Rendering::Ray get_ray(double u, double v) {
				const auto rd = _lens_radius * Math::Vec2::random_in_unit_disk();
				const auto offset = _u * rd.x() + _v * rd.y();
				return Rendering::Ray(
					_origin + offset,
					_center + u * _horizontal + v * _vertical - _origin - offset);
			}

		private:
			static Camera _from(
				const Math::Vec3& from,
				const Math::Vec3& at,
				const Math::Vec3& up,
				double half_width,
				double half_height,
				double aperture,
				double focal_distance)
			{
				// get the orthonormal basis
				const auto w = (from - at).norm();
				const auto u = Math::Vec3::cross(up, w).norm();
				const auto v = Math::Vec3::cross(w, u).norm();

				return Camera(
					from,
					from - focal_distance * w,
					2.0 * half_width * focal_distance * u,
					2.0 * half_height * focal_distance * v,
					u,
					v,
					w,
					aperture / 2.0);
			}
		};
	}
}