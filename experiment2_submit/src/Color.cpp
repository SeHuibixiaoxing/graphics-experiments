#include "Color.h"

void Color::write_color(std::ostream& out, color pixel_color, int samples_per_pixel)
{
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();
		
	auto scale = 1.0 / samples_per_pixel;
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);

	out << (int)(256 * Defs::clamp(r, 0.0, 0.999)) << ' '
		<< (int)(256 * Defs::clamp(g, 0.0, 0.999)) << ' '
		<< (int)(256 * Defs::clamp(b, 0.0, 0.999)) << '\n';
}
