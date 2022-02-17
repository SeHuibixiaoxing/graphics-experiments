#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "Material.h"
#include "vec3.h"

class Sphere : public Hittable 
{
public:
	Sphere() {}
	Sphere(point3 cen, double r, std::shared_ptr<Material> m) : center(cen), radius(r), mat_ptr(m) {};

	virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
private:
	point3 center;
	double radius;
	std::shared_ptr<Material> mat_ptr;
};

#endif