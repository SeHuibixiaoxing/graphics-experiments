#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "vec3.h"
#include "Material.h"

class Lambertian : public Material
{
public:
	Lambertian(const color& a) : albedo(a) {}
	virtual bool scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const override;

private:
	color albedo;
};
#endif