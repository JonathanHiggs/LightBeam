#include <iostream>

#include "bitmap.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "constants.hpp"
#include "sphere.hpp"
#include "hittable_list.hpp"
#include "lamberitian_diffuse.hpp"
#include "metal.hpp"


// https://raytracing.github.io/books/RayTracingInOneWeekend.html


Color ray_color(
	const Ray& ray,
	const IHittable& hittable,
	int max_depth = 20,
	int depth = 0)
{
	HitRecord hitRecord;

	if (depth >= max_depth)
		return Color::black;

	if (hittable.hit(ray, 1e-10, infinity, hitRecord))
	{
		Ray scattered;
		Color attenuation;

		if (hitRecord.meterial()->scatter(ray, hitRecord, attenuation, scattered))
			return attenuation * ray_color(scattered, hittable, max_depth, ++depth);

		return Color::black;
	}

	auto unit_direction = ray.direction().norm();
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return Color(Vec3::interpolate(Vec3::one, Vec3(0.5, 0.7, 1.0), t));
}


int main()
{
	const unsigned int width = 1000;
	const unsigned int height = 500;
	const int sample_rate = 4;

	auto image = Bitmap(width, height);
	auto camera = Camera(
		Vec3::unit_z,
		-Vec3::unit_z,
		4.0 * Vec3::unit_x,
		4.0 * (double(height) / double(width)) * Vec3::unit_y);

	auto hittables = HittableList();

	hittables.add(std::make_shared<Sphere>(
		Vec3(0, 0, -1), 0.5, std::make_shared<LambertianDiffuse>(Vec3(0.7, 0.3, 0.3))));

	hittables.add(std::make_shared<Sphere>(
		Vec3(0, -100.5, -1), 100, std::make_shared<LambertianDiffuse>(Vec3(0.8, 0.8, 0.0))));

	hittables.add(std::make_shared<Sphere>(
		Vec3(1, 0, -1), 0.3, std::make_shared<Metal>(Vec3(0.8, 0.6, 0.2), 0.01)));

	hittables.add(std::make_shared<Sphere>(
		Vec3(-1, 0, -1), 0.4, std::make_shared<Metal>(Vec3(0.8, 0.8, 0.8), 0.2)));

	hittables.add(std::make_shared<Sphere>(
		Vec3(2, 0, -1), 0.6, std::make_shared<LambertianDiffuse>(Vec3(0.8, 0.2, 1.0))));

	hittables.add(std::make_shared<Sphere>(
		Vec3(-2, 0, -1), 0.3, std::make_shared<LambertianDiffuse>(Vec3(0.2, 0.9, 0.5))));


	for (auto j = 0; j < height; ++j)
	{
		std::cerr << "\rScanlines remaining " << height - j << ' ' << std::flush;

		for (auto i = 0; i < width; ++i)
		{
			Color col = Color::black;
			auto samples = 0;

			for (auto jx = 0; jx < sample_rate; ++jx)
			{
				auto jd = double(jx) / double(sample_rate);

				for (auto ix = 0; ix < sample_rate; ++ix)
				{
					samples++;
					auto id = double(ix) / double(sample_rate);

					auto u = (((double(i) + id) / width) - 0.5);
					auto v = (0.5 - (double(j) + jd) / height);

					auto ray = camera.get_ray(u, v);
					col += ray_color(ray, hittables);
				}
			}

			col /= double(samples);
			image.set_pixel(i, j, col.to_rgb());
		}
	}

	std::cerr << std::endl << "Completed" << std::endl;

	image.save_image("image3.bmp");
}