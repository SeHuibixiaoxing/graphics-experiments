#include "defs.h"

double Defs::degress_to_radians(double degrees)
{
	return degrees * pi / 180.0;
}

double Defs::random_double()
{
	return rand() / (RAND_MAX + 1.0);
}

double Defs::random_double(double min, double max)
{
	return min + (max - min) * random_double();
}

double Defs::clamp(double x, double min, double max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

const double Defs::infinity = std::numeric_limits<double>::infinity();
const double Defs::pi = 3.1415926535897932385;
