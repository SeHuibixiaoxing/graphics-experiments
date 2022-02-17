#include "ray.h"

point3 Ray::origin() const
{
	return this->orig;
}

vec3 Ray::direction() const
{
	return this->dir;
}

point3 Ray::at(double t) const
{
	return orig + t * dir;
}
