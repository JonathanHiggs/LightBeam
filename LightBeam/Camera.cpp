#include "Camera.hpp"
#include "Random.hpp"
#include "Utils.hpp"


namespace LightBeam
{
	namespace Scene
	{
		Camera::Camera(
			const Math::Vec3& origin,
			const Math::Vec3& center,
			const Math::Vec3& horizontal,
			const Math::Vec3& vertical,
			const Math::Vec3& u,
			const Math::Vec3& v,
			const Math::Vec3& w,
			double lens_radius,
			double begin_time,
			double end_time)
			: _origin{ origin }
			, _center{ center }
			, _horizontal{ horizontal }
			, _vertical{ vertical }
			, _u{ u }
			, _v{ v }
			, _w{ w }
			, _lens_radius{ lens_radius }
			, _begin_time{ begin_time }
			, _end_time{ end_time }
		{ }

		Camera Camera::from_vfov(
			const Math::Vec3& from,
			const Math::Vec3& at,
			const Math::Vec3& up,
			double vfov,
			double aspect_ratio,
			double aperture,
			double focal_distance,
			double begin_time,
			double end_time)
		{
			const auto theta = Util::degrees_to_radians(vfov);
			const auto half_height = std::tan(theta / 2.0);
			const auto half_width = aspect_ratio * half_height;

			return _from(from, at, up, half_width, half_height, aperture, focal_distance, begin_time, end_time);
		}

		Camera Camera::from_hfov(
			const Math::Vec3& from,
			const Math::Vec3& at,
			const Math::Vec3& up,
			double hfov,
			double aspect_ratio,
			double aperture,
			double focal_distance,
			double begin_time,
			double end_time)
		{
			auto theta = Util::degrees_to_radians(hfov);
			auto half_width = std::tan(theta / 2.0);
			auto half_height = half_width / aspect_ratio;

			return _from(from, at, up, half_width, half_height, aperture, focal_distance, begin_time, end_time);
		}

		Rendering::Ray Camera::get_ray(double u, double v) const
		{
			const auto rd = _lens_radius * Math::Vec2::random_in_unit_disk();
			const auto offset = _u * rd.x() + _v * rd.y();

			return Rendering::Ray(
				_origin + offset,
				_center + u * _horizontal + v * _vertical - _origin - offset,
				Util::random_double(_begin_time, _end_time));
		}

		Camera Camera::_from(
			const Math::Vec3& from,
			const Math::Vec3& at,
			const Math::Vec3& up,
			double half_width,
			double half_height,
			double aperture,
			double focal_distance,
			double begin_time,
			double end_time)
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
				aperture / 2.0,
				begin_time,
				end_time);
		}
	}
}