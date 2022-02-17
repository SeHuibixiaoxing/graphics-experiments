#ifndef DEFS_H
#define DEFS_H

#include <cmath>
#include <limits>
#include <memory>


class Defs
{
public:
	static const double infinity;
	static const double pi;

	static double degress_to_radians(double degrees);
	static double random_double();
	static double random_double(double min, double max);
	static double clamp(double x, double min, double max);
};

#endif