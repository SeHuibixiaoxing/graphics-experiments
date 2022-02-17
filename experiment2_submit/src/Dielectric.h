#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "Material.h"
#include "defs.h"

class Dielectric : public Material
{
public:
	Dielectric(double index_of_refraction) : ir(index_of_refraction) {}
	virtual bool scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const override;
private:
	double ir;
	static double reflectance(double cosine, double ref_idx);
};
#endif