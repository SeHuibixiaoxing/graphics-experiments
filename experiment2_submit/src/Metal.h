#ifndef METAL_H
#define METAL_H

#include "vec3.h"
#include "Material.h"

class Metal : public Material
{
public:
	Metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}
	virtual bool scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const override;
private:
	color albedo;
	double fuzz;
};

#endif