#ifndef HITTABLE_H
#define HITTABLE_H

#include "vec3.h"
#include "ray.h"
#include "defs.h"

class Material;

struct HitRecord
{
public:
	point3 p;
	vec3 normal;
	std::shared_ptr<Material> mat_ptr;
	double t;
	bool front_face;

	void set_face_normal(const Ray& r, const vec3& outward_normal)
	{
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class Hittable
{
public:
	virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};

#endif
