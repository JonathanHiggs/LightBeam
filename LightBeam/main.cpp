#include <iostream>

#include "bitmap.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "constants.hpp"
#include "sphere.hpp"
#include "hittable_list.hpp"



Color ray_color(const Ray& ray, const IHittable& hittable)
{
	HitRecord hitRecord;

	if (hittable.hit(ray, 1e-10, infinity, hitRecord))
		return Color::from_norm_vec(hitRecord.normal());

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
	auto camera = Camera();

	auto hittables = HittableList();
	hittables.add(std::make_shared<Sphere>(Vec3( 0,   0, -1), 0.5));
	hittables.add(std::make_shared<Sphere>(Vec3(0, -100.5, -1), 100));

	for (auto j = 0; j < height; ++j)
	{
		std::cerr << "\rScanlines remaining " << height - j << "     " << std::flush;

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

					auto u = 4.0 * (((double(i) + id) / width) - 0.5);
					auto v = 2.0 * (0.5 - (double(j) + jd) / height);

					auto ray = camera.get_ray(u, v);
					col += ray_color(ray, hittables);
				}
			}

			col /= double(samples);
			image.set_pixel(i, j, col.to_rgb());
		}
	}

	image.save_image("image4.bmp");
}