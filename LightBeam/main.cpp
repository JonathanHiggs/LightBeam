#include <chrono>
#include <iostream>

#include "Bitmap.hpp"
#include "BoundingVolumeNode.hpp"
#include "Box.hpp"
#include "Camera.hpp"
#include "CheckerTexture.hpp"
#include "Color.hpp"
#include "CosinePDF.hpp"
#include "ConstantMedium.hpp"
#include "Constants.hpp"
#include "ConstantTexture.hpp"
#include "Dielectric.hpp"
#include "DiffuseLight.hpp"
#include "HittableList.hpp"
#include "HittablePDF.hpp"
#include "ImageTexture.hpp"
#include "LamberitianDiffuse.hpp"
#include "Metal.hpp"
#include "MovingSphere.hpp"
#include "NoiseTexture.hpp"
#include "Perlin.hpp"
#include "Sphere.hpp"
#include "Timer.hpp"
#include "Translate.hpp"
#include "XYRectangle.hpp"
#include "XZRectangle.hpp"
#include "YRotation.hpp"
#include "YZRectangle.hpp"


// https://raytracing.github.io/books/RayTracingInOneWeekend.html
// https://raytracing.github.io/books/RayTracingTheNextWeek.html
// https://raytracing.github.io/books/RayTracingTheRestOfYourLife.html


using namespace LightBeam;
using namespace LightBeam::Image;
using namespace LightBeam::Materials;
using namespace LightBeam::Math;
using namespace LightBeam::Noise;
using namespace LightBeam::Rendering;
using namespace LightBeam::Scene;
using namespace LightBeam::Shapes;
using namespace LightBeam::Textures;
using namespace LightBeam::Util;
using namespace LightBeam::Volumes;


Color ray_color(
	const Ray& ray,
	const Color& background,
	const IHittable& hittable,
	int max_depth = 50,
	int depth = 0)
{
	double scatter_pdf;
	Color albedo;
	Ray scattered;
	HitRecord hit_record;

	if (depth >= max_depth)
		return Color::BLACK;

	if (!hittable.hit(ray, 1e-10, Util::infinity, hit_record))
		return background;

	Color emitted = !!hit_record.meterial()
		? hit_record.meterial()->emitted(ray, hit_record, hit_record.uv(), hit_record.point())
		: Color::BLACK;

	if (!hit_record.meterial()->scatter(ray, hit_record, albedo, scattered, scatter_pdf))
		return emitted;

	auto light_shape = std::make_shared<const XYRectangle>(213, 343, 227, 332, 554, std::make_shared<LambertianDiffuse>(Color::BLACK));
	auto pdf = HittablePDF(light_shape, hit_record.point());

	scattered = Ray(hit_record.point(), pdf.generate(), ray.time());
	scatter_pdf = pdf.value(scattered.direction());

	double scattered_pdf = hit_record.meterial()->scattering_pdf(ray, hit_record, scattered);
	Color scattered_color = ray_color(scattered, background, hittable, max_depth, ++depth);

	return emitted + albedo * scattered_pdf * scattered_color / scatter_pdf;
}


BoundingVolumeNode random_scene()
{
	auto hittables = std::vector<IHittableCPtr>();

	auto checker = std::make_shared<const CheckersTexture>(
		Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9));

	hittables.push_back(std::make_shared<Sphere>(
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
					hittables.push_back(std::make_shared<MovingSphere>(
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
					hittables.push_back(std::make_shared<Sphere>(
						center, radius, std::make_shared<Metal>(albedo, fuzz)));
				}
				else {
					// glass
					auto refractive_index = Util::random_double(1.4, 2.4);
					hittables.push_back(std::make_shared<Sphere>(
						center, radius, std::make_shared<Dielectric>(refractive_index)));
				}
			}
		}
	}

	hittables.push_back(std::make_shared<Sphere>(
		Vec3(-4, 1, 0), 1.0, std::make_shared<LambertianDiffuse>(Vec3(0.4, 0.2, 0.1))));

	hittables.push_back(std::make_shared<Sphere>(
		Vec3(0, 1, 0), 1.0, std::make_shared<Dielectric>(1.5)));

	hittables.push_back(std::make_shared<Sphere>(
		Vec3(4, 1, 0), 1.0, std::make_shared<Metal>(Vec3(0.7, 0.6, 0.5), 0.0)));

	return BoundingVolumeNode(hittables, 0.0, 1.0);
}


BoundingVolumeNode two_perlin_spheres()
{
	auto shapes = std::vector<IHittableCPtr>();

	auto pertext = std::make_shared<const NoiseTexture>(Perlin(), 10.0);

	shapes.push_back(std::make_shared<const Sphere>(
		Vec3(0, -1000, 0), 1000, std::make_shared<LambertianDiffuse>(pertext)));

	shapes.push_back(std::make_shared<const Sphere>(
		Vec3(0, 2, 0), 2, std::make_shared<const LambertianDiffuse>(pertext)));

	return BoundingVolumeNode(shapes, 0.0, 1.0);
}


BoundingVolumeNode earth()
{
	auto shapes = std::vector<IHittableCPtr>();

	shapes.push_back(std::make_shared<const Sphere>(
		Vec3(0, -1001, 0), 1000, std::make_shared<Metal>(Vec3::one, 0.0)));

	auto earth_texture =
		std::make_shared<const ImageTexture>(
			std::make_shared<const Bitmap>("earthmap.bmp"));

	shapes.push_back(std::make_shared<const Sphere>(
		Vec3(0, 1, 0), 2, std::make_shared<const LambertianDiffuse>(earth_texture)));

	return BoundingVolumeNode(shapes, 0.0, 1.0);
}


BoundingVolumeNode lighting()
{
	auto shapes = std::vector<IHittableCPtr>();

	auto perlin_texture = std::make_shared<const NoiseTexture>(Perlin(), 10.0);

	shapes.push_back(std::make_shared<const Sphere>(
		Vec3(0, -1000, 0), 1000, std::make_shared<LambertianDiffuse>(perlin_texture)));

	shapes.push_back(std::make_shared<Sphere>(
		Vec3(-3, 2, 0.5), 2, std::make_shared<Metal>(Vec3::one, 0)));

	shapes.push_back(std::make_shared<const Sphere>(
		Vec3(0, 2, 0), 2, std::make_shared<const LambertianDiffuse>(perlin_texture)));

	shapes.push_back(std::make_shared<Sphere>(
		Vec3(3, 2, -0.5), 2, std::make_shared<Dielectric>(1.5)));

	shapes.push_back(std::make_shared<const XYRectangle>(
		3, 5, 1, 3, -2, std::make_shared<const DiffuseLight>(Color(0.90, 6.0, 0.90))));

	shapes.push_back(std::make_shared<const Sphere>(
		Vec3(0, 5, 0), -0.8, std::make_shared<const DiffuseLight>(Color(0.90, 0.90, 6.0))));

	return BoundingVolumeNode(shapes, 0.0, 1.0);
}


BoundingVolumeNode cornell_box()
{
	auto shapes = std::vector<IHittableCPtr>();

	auto red   = std::make_shared<const LambertianDiffuse>(Color(0.65, 0.05, 0.05));
	auto white = std::make_shared<const LambertianDiffuse>(Color(0.73, 0.73, 0.73));
	auto green = std::make_shared<const LambertianDiffuse>(Color(0.12, 0.45, 0.15));
	auto light = std::make_shared<const DiffuseLight>(Color(15, 15, 15));

	shapes.push_back(std::make_shared<const YZRectangle>(0, 555, 0, 555, 555, green));	// left
	shapes.push_back(std::make_shared<const YZRectangle>(0, 555, 0, 555, 0,   red));		// right
	shapes.push_back(std::make_shared<const XZRectangle>(0, 555, 0, 555, 0,   white));	// floor
	shapes.push_back(std::make_shared<const XZRectangle>(0, 555, 0, 555, 555, white));	// top
	shapes.push_back(std::make_shared<const XYRectangle>(0, 555, 0, 555, 555, white));	// back

	shapes.push_back(std::make_shared<const XZRectangle>(213, 343, 227, 332, 554, light, true));	// light

	shapes.push_back(
		std::make_shared<const Translate>(Vec3(265, 0, 295),
			std::make_shared<const YRotation>(15,
				std::make_shared<const Box>(Vec3(0, 0, 0), Vec3(165, 330, 165), white))));

	shapes.push_back(
		std::make_shared<const Translate>(Vec3(130, 0, 65),
			std::make_shared<const YRotation>(-18,
				std::make_shared<const Box>(Vec3(0, 0, 0), Vec3(165, 165, 165), white))));

	return BoundingVolumeNode(shapes, 0.0, 1.0);
}


BoundingVolumeNode cornell_smoke()
{
	auto shapes = std::vector<IHittableCPtr>();

	auto red   = std::make_shared<const LambertianDiffuse>(Color(0.65, 0.05, 0.05));
	auto white = std::make_shared<const LambertianDiffuse>(Color(0.73, 0.73, 0.73));
	auto green = std::make_shared<const LambertianDiffuse>(Color(0.12, 0.45, 0.15));
	auto light = std::make_shared<const DiffuseLight>(Color(7, 7, 7));

	shapes.push_back(std::make_shared<const YZRectangle>(0, 555, 0, 555, 555, green));	// left
	shapes.push_back(std::make_shared<const YZRectangle>(0, 555, 0, 555, 0,   red));	// right
	shapes.push_back(std::make_shared<const XZRectangle>(0, 555, 0, 555, 0,   white));	// floor
	shapes.push_back(std::make_shared<const XZRectangle>(0, 555, 0, 555, 555, white));	// top
	shapes.push_back(std::make_shared<const XYRectangle>(0, 555, 0, 555, 555, white));	// back

	shapes.push_back(std::make_shared<const XZRectangle>(113, 443, 127, 432, 554, light));	// light

	const auto box1 =
		std::make_shared<const Translate>(Vec3(265, 0, 295),
			std::make_shared<const YRotation>(15,
				std::make_shared<const Box>(Vec3(0, 0, 0), Vec3(165, 330, 165), white)));

	shapes.push_back(
		std::make_shared<const ConstantMedium>(
			box1, 0.01, std::make_shared<const ConstantTexture>(Image::Color::BLACK)));

	const auto box2 =
		std::make_shared<const Translate>(Vec3(130, 0, 65),
			std::make_shared<const YRotation>(-18,
				std::make_shared<const Box>(Vec3(0, 0, 0), Vec3(165, 165, 165), white)));

	shapes.push_back(
		std::make_shared<const ConstantMedium>(
			box2, 0.1, std::make_shared<const ConstantTexture>(Image::Color::WHITE)));

	return BoundingVolumeNode(shapes, 0.0, 1.0);
}


BoundingVolumeNode final_scene()
{
	auto boxes = std::vector<IHittableCPtr>();

	auto ground =
		std::make_shared<LambertianDiffuse>(
			std::make_shared<ConstantTexture>(Color(0.48, 0.83, 0.53)));

	const int boxes_per_side = 20;
	for (int i = 0; i < boxes_per_side; i++)
	{
		for (int j = 0; j < boxes_per_side; j++)
		{
			auto x0 = -1000.0 + i * 100.0;
			auto y0 = 0.0;
			auto z0 = -1000.0 + j * 100.0;

			auto x1 = x0 + 100.0;
			auto y1 = random_double(1, 101);
			auto z1 = z0 + 100.0;

			boxes.push_back(
				std::make_shared<Box>(Vec3(x0, y0, z0), Vec3(x1, y1, z1), ground));
		}
	}

	auto objects = std::vector<IHittableCPtr>();

	objects.push_back(
		std::make_shared<XZRectangle>(
			100, 500, 100, 500, 750,
			std::make_shared<DiffuseLight>(Color::WHITE, 7.0)));

	objects.push_back(
		std::make_shared<MovingSphere>(
			Vec3(400, 400, 200),
			Vec3(430, 400, 200),
			0, 1, 50,
			std::make_shared<LambertianDiffuse>(Color(0.7, 0.3, 0.1))));

	objects.push_back(
		std::make_shared<Sphere>(
			Vec3(260, 150, 45),
			50.0,
			std::make_shared<Dielectric>(1.5)));

	objects.push_back(
		std::make_shared<Sphere>(
			Vec3(30, 170, 145),
			50,
			std::make_shared<Metal>(Color(0.8, 0.8, 0.9), 0.0)));

	objects.push_back(
		std::make_shared<ConstantMedium>(
			std::make_shared<Sphere>(
				Vec3(360, 150, 145),
				70,
				std::make_shared<LambertianDiffuse>(Color(0.2, 0.4, 0.9))),
			0.05,
			std::make_shared<ConstantTexture>(Color(0.2, 0.4, 0.9))));

	objects.push_back(
		std::make_shared<Sphere>(
			Vec3(510, 270, 420),
			100,
			std::make_shared<LambertianDiffuse>(
				std::make_shared<ImageTexture>(
					std::make_shared<Bitmap>("earthmap.bmp")))));

	objects.push_back(
		std::make_shared<Sphere>(
			Vec3(230, 280, 300),
			80,
			std::make_shared<LambertianDiffuse>(
				std::make_shared<NoiseTexture>(Perlin(), 1e-5))));

	objects.push_back(
		std::make_shared<Sphere>(
			Vec3(220, 280, 300),
			80,
			std::make_shared<LambertianDiffuse>(
				std::make_shared<NoiseTexture>(Perlin(), 1000.0))));

	auto white = std::make_shared<LambertianDiffuse>(Color(0.73, 0.73, 0.73));
	auto spheres = std::vector<IHittableCPtr>();
	for (auto i = 0; i < 1000; i++)
		spheres.push_back(
			std::make_shared<Sphere>(
				Vec3(-120, 280, 300) + Vec3::random(0, 165), 10, white));

	objects.push_back(std::make_shared<BoundingVolumeNode>(spheres, 0.0, 1.0));

	return BoundingVolumeNode(
	 	std::make_shared<const BoundingVolumeNode>(boxes, 0.0, 1.0),
		std::make_shared<const BoundingVolumeNode>(objects, 0.0, 1.0));
}


Camera random_scene_camera(double aspect_ratio)
{
	const auto from = Vec3(13, 2, 3);
	const auto at = Vec3(0, 1, 0);
	const auto up = Vec3::unit_y;

	return Camera::from_hfov(
		from, at, up, 30.0, aspect_ratio, 0.05, 10.0, 0.0, 0.2);
}


Camera cornell_camera(double aspect_ratio)
{
	const auto from = Vec3(278, 278, -800);
	const auto at = Vec3(278, 278, 0);
	const auto up = Vec3::unit_y;

	return Camera::from_vfov(
		from, at, up, 20.0, aspect_ratio, 0.0, 10.0, 0.0, 1.0);
}


Camera final_camera(double aspect_ratio)
{
	const auto from = Vec3(550, 310, -750);
	const auto at = Vec3(250, 250, 300);
	const auto up = Vec3::unit_y;

	return Camera::from_hfov(
		from, at, up, 20.0, aspect_ratio, 0.0, 10.0, 0.0, 1.0);
}


int main()
{
	const unsigned int width = 500; // 384 * 2;
	const unsigned int height = 500; // 216 * 2;
	auto aspect_ratio = double(width) / double(height);

	const int sample_rate = 4;

	auto image = Bitmap(width, height);

	const auto camera = cornell_camera(aspect_ratio);
	auto bvn = cornell_box();

	{
		Timer timer(&std::cerr, "Rendering");

		long long rays = 0;
		for (auto j = 0; j < height; ++j)
		{
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
						col += ray_color(ray, Color(0.001, 0.001, 0.001), bvn);
					}
				}

				col /= double(samples);
				image.set_pixel(i, j, col.to_rgb());
			}

			std::cerr << "\rScanlines completed: " << j + 1 << " / " << height << " : " << (int(j) + 1) * 100.0 / height << "% : " << rays / 1000000 << "M rays processed" << std::flush;
		}

		std::cerr << std::endl;
	}

	{
		Timer timer(&std::cerr, "Saving");
		image.save_image("../images/image084.bmp");
	}
}