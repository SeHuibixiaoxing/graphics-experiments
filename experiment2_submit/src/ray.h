#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray
{
public:
	Ray() {}
	Ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}
	point3 origin() const;
	vec3 direction() const;
	point3 at(double t) const;

private:
	point3 orig;
	vec3 dir;
};

#endif