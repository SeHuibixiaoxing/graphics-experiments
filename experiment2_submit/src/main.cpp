#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "color.h"
#include "HittableList.h"
#include "sphere.h"
#include "camera.h"
#include "defs.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"


color ray_color(const Ray& r, const Hittable& world, int depth)
{
	HitRecord rec;
	if (depth <= 0)
		return color(0, 0, 0);
	if (world.hit(r, 0.001, Defs::infinity, rec))
	{
		Ray scattered;
		color attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) 
			return attenuation * ray_color(scattered, world, depth - 1);
		return color(0, 0, 0);
	}
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}
HittableList random_scene() {
	HittableList world;

	auto ground_material = std::make_shared<Lambertian>(color(0.5, 0.5, 0.5));
	world.add(std::make_shared<Sphere>(point3(0, -1000, 0), 1000, ground_material));

	for (int a = -11; a < 11; ++a) {
		for (int b = -11; b < 11; ++ b) {
			auto choose_mat = Defs::random_double();
			point3 center(a + 0.9 * Defs::random_double(), 0.2, b + 0.9 * Defs::random_double());

			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
				std::shared_ptr<Material> sphere_material;

				if (choose_mat < 0.8) {
					auto albedo = color::random() * color::random();
					sphere_material = std::make_shared<Lambertian>(albedo);
					world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95) {
					auto albedo = color::random(0.5, 1);
					auto fuzz = Defs::random_double(0, 0.5);
					sphere_material = std::make_shared<Metal>(albedo, fuzz);
					world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else {
					sphere_material = std::make_shared<Dielectric>(1.5);
					world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = std::make_shared<Dielectric>(1.5);
	world.add(std::make_shared<Sphere>(point3(0, 1, 0), 1.0, material1));

	auto material2 = std::make_shared<Lambertian>(color(0.4, 0.2, 0.1));
	world.add(std::make_shared<Sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = std::make_shared<Metal>(color(0.7, 0.6, 0.5), 0.0);
	world.add(std::make_shared<Sphere>(point3(4, 1, 0), 1.0, material3));

	return world;
}


int main()
{
	freopen("image.ppm", "w", stdout);

	//图像属性
	const auto aspect_ratio = 3.0 / 2.0;
	const int image_width = 1200;
	const int image_height = (int)(image_width / aspect_ratio);
	const int samples_per_pixel = 10;
	const int max_depth = 50;

	//物体
	auto world = random_scene();

	//摄像机
	point3 lookfrom(13, 2, 3);
	point3 lookat(0, 0, 0);
	vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;
	Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i)
		{
			color pixel_color(0, 0, 0);
			for (int k = 0; k < samples_per_pixel; ++k)
			{
				auto u = ((double)i + Defs::random_double()) / (image_width - 1);
				auto v = ((double)j + Defs::random_double()) / (image_height - 1);
				Ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);

			}
			Color::write_color(std::cout, pixel_color, samples_per_pixel);
		}
	}
	std::cerr << "\nDone.\n";

}