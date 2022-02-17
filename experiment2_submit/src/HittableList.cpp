#include "HittableList.h"

HittableList::HittableList(std::shared_ptr<Hittable> object)
{
	add(object);
}

void HittableList::clear()
{
	objects.clear();
}

void HittableList::add(std::shared_ptr<Hittable> object)
{
	objects.push_back(object);
}

bool HittableList::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
	HitRecord tmp_rec;
	bool hit_anything = false;
	auto closest_so_far = t_max;

	for (const auto& object : objects)
	{
		if (object->hit(r, t_min, closest_so_far, tmp_rec))
		{
			hit_anything = true;
			closest_so_far = tmp_rec.t;
			rec = tmp_rec;
		}
	}

	return hit_anything;
}
