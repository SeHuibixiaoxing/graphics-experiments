#include "Lambertian.h"

bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const
{
    auto scatter_direction = rec.normal + vec3::random_unit_vector();

    if (scatter_direction.near_zero()) scatter_direction = rec.normal;

    scattered = Ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}
