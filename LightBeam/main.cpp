#include <chrono>
#include <iostream>

#include "Bitmap.hpp"
#include "BoundingVolumeNode.hpp"
#include "Camera.hpp"
#include "CheckerTexture.hpp"
#include "Color.hpp"
#include "Constants.hpp"
#include "Dielectric.hpp"
#include "HittableList.hpp"
#include "LamberitianDiffuse.hpp"
#include "Metal.hpp"
#include "MovingSphere.hpp"
#include "NoiseTexture.hpp"
#include "Perlin.hpp"
#include "Sphere.hpp"


// https://raytracing.github.io/books/RayTracingInOneWeekend.html
// https://raytracing.github.io/books/RayTracingTheNextWeek.html


using namespace LightBeam;
using namespace LightBeam::Image;
using namespace LightBeam::Materials;
using namespace LightBeam::Math;
using namespace LightBeam::Noise;
using namespace LightBeam::Rendering;
using namespace LightBeam::Scene;
using namespace LightBeam::Shapes;
using namespace LightBeam::Textures;


Color ray_color(
	const Ray& ray,
	const IHittable& hittable,
	int max_depth = 50,
	int depth = 0)
{
	HitRecord hit_record;

	if (depth >= max_depth)
		return Color::BLACK;

	if (hittable.hit(ray, 1e-10, Util::infinity, hit_record))
	{
		Ray scattered;
		Color attenuation;

		if (hit_record.meterial()->scatter(ray, hit_record, attenuation, scattered))
			return attenuation * ray_color(scattered, hittable, max_depth, ++depth);

		return Color::BLACK;
	}

	auto unit_direction = ray.direction().norm();
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return Color(Vec3::interpolate(Vec3::one, Vec3(0.5, 0.7, 1.0), t));
}


std::vector<std::shared_ptr<const IHittable>> random_scene() {
	auto hittables = std::vector<std::shared_ptr<const IHittable>>();

	auto checker = std::make_shared<const CheckersTexture>(
		Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9));

	hittables.emplace_back(std::make_shared<Sphere>(
		Vec3(0, -1000, 0), 1000, std::make_shared<LambertianDiffuse>(checker)));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			const auto choose_mat = Util::random_double();
			const auto radius = 0.2 + choose_mat / 10.0;
			const auto center = Vec3(
				a + (0.8 - radius) * Util::random_double(),
				radius,
				b + (0.8 - radius) * Util::random_double());

			if ((center - Vec3(4, 0.2, 0)).length() > 0.9) {
				if (choose_mat < 0.8) {
					// diffuse
					auto albedo = Vec3::random() * Vec3::random();
					hittables.emplace_back(std::make_shared<MovingSphere>(
						center,
						center + Vec3(0, Util::random_double(0, 0.5), 0),
						0.0,
						1.0,
						radius,
						std::make_shared<LambertianDiffuse>(albedo)));
				}
				else if (choose_mat < 0.95) {
					// metal
					auto albedo = Vec3::random(0.5, 1);
					auto fuzz = Util::random_double(0, 0.5);
					hittables.emplace_back(std::make_shared<Sphere>(
						center, radius, std::make_shared<Metal>(albedo, fuzz)));
				}
				else {
					// glass
					auto refractive_index = Util::random_double(1.4, 2.4);
					hittables.emplace_back(std::make_shared<Sphere>(
						center, radius, std::make_shared<Dielectric>(refractive_index)));
				}
			}
		}
	}

	hittables.emplace_back(std::make_shared<Sphere>(
		Vec3(-4, 1, 0), 1.0, std::make_shared<LambertianDiffuse>(Vec3(0.4, 0.2, 0.1))));

	hittables.emplace_back(std::make_shared<Sphere>(
		Vec3(0, 1, 0), 1.0, std::make_shared<Dielectric>(1.5)));

	hittables.emplace_back(std::make_shared<Sphere>(
		Vec3(4, 1, 0), 1.0, std::make_shared<Metal>(Vec3(0.7, 0.6, 0.5), 0.0)));

	return hittables;
}

std::vector<std::shared_ptr<const IHittable>> two_perlin_spheres()
{
	auto shapes = std::vector<std::shared_ptr<const IHittable>>();

	auto pertext = std::make_shared<const NoiseTexture>(Perlin(), 10.0);

	shapes.emplace_back(std::make_shared<const Sphere>(
		Vec3(0, -1000, 0), 1000, std::make_shared<LambertianDiffuse>(pertext)));

	shapes.emplace_back(std::make_shared<const Sphere>(
		Vec3(0, 2, 0), 2, std::make_shared<const LambertianDiffuse>(pertext)));

	return shapes;
}

int main()
{
	const unsigned int width = 2000;
	const unsigned int height = 1000;
	auto aspect_ratio = double(width) / double(height);

	const int sample_rate = 4;

	auto image = Bitmap(width, height);

	const auto from = Vec3(13, 2, 3);
	const auto at = Vec3(0, 0, 0);
	const auto up = Vec3::unit_y;

	auto camera = Camera::from_hfov(
		from,
		at,
		up,
		20.0,
		aspect_ratio,
		0.05,
		10.0,
		0.0,
		0.2);

	//auto hittables = random_scene();
	auto hittables = two_perlin_spheres();
	auto bvn = BoundingVolumeNode(hittables, 0.0, 0.5);

	auto begin_time = std::chrono::high_resolution_clock::now();

	long long rays = 0;
	for (auto j = 0; j < height; ++j)
	{
		std::cerr << "\rScanlines completed: " << j << " / " << height << " : " << j * 100.0 / height  << "% : " << rays / 1000000 << "M rays processed" << std::flush;

		for (auto i = 0; i < width; ++i)
		{
			Color col = Color::BLACK;
			auto samples = 0;

			for (auto jx = 0; jx < sample_rate; ++jx)
			{
				auto jd = double(jx) / double(sample_rate);

				for (auto ix = 0; ix < sample_rate; ++ix)
				{
					samples++;
					rays++;
					auto id = double(ix) / double(sample_rate);

					auto u = 2.0 * (((double(i) + id) / width) - 0.5);
					auto v = 2.0 * (0.5 - (double(j) + jd) / height);

					auto ray = camera.get_ray(u, v);
					col += ray_color(ray, bvn);
				}
			}

			col /= double(samples);
			image.set_pixel(i, j, col.to_rgb());
		}
	}

	auto end_time = std::chrono::high_resolution_clock::now();
	auto elapsed = end_time - begin_time;
	auto seconds = elapsed.count() * 1e-9;

	std::cerr << std::endl << "Completed in " << seconds << "s" << std::endl;

	image.save_image("../images/image038.bmp");
}