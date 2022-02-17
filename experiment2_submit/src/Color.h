#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "defs.h"
#include <iostream>

class Color
{
public:
	static void write_color(std::ostream& out, color pixel_color, int samples_per_pixel);
};

#endif