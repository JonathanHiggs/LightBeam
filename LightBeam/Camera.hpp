#pragma once


#include "Ray.hpp"
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
			double _begin_time;
			double _end_time;

		public:
			Camera(
				const Math::Vec3& origin,
				const Math::Vec3& center,
				const Math::Vec3& horizontal,
				const Math::Vec3& vertical,
				const Math::Vec3& u,
				const Math::Vec3& v,
				const Math::Vec3& w,
				double lens_radius,
				double begin_time,
				double end_time);

			static Camera from_vfov(
				const Math::Vec3& from,
				const Math::Vec3& at,
				const Math::Vec3& up,
				double vfov,
				double aspect_ratio,
				double aperture,
				double focal_distance,
				double begin_time,
				double end_time);

			static Camera from_hfov(
				const Math::Vec3& from,
				const Math::Vec3& at,
				const Math::Vec3& up,
				double hfov,
				double aspect_ratio,
				double aperture,
				double focal_distance,
				double begin_time,
				double end_time);

			Rendering::Ray get_ray(double u, double v) const;

		private:
			static Camera _from(
				const Math::Vec3& from,
				const Math::Vec3& at,
				const Math::Vec3& up,
				double half_width,
				double half_height,
				double aperture,
				double focal_distance,
				double begin_time,
				double end_time);
		};
	}
}