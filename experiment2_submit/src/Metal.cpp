#include "Metal.h"

bool Metal::scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const
{
    vec3 reflected = vec3::reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = Ray(rec.p, reflected + fuzz * vec3::random_in_unit_sphere());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}
