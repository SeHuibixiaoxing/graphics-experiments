#ifndef VEC3_H
#define VEC3_H
#include <cmath>
#include <fstream>
#include "defs.h"

class vec3
{
public:
	vec3() : e{0, 0, 0} {}
	vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

	double x() const;
	double y() const;
	double z() const;

	vec3 operator-() const;
	double operator[](int i) const;
	double& operator[](int i);
	vec3& operator+=(const vec3& v);
	vec3& operator*=(const double t);
	vec3& operator/=(const double t);
	double length() const;
	double length_squared() const;
	bool near_zero() const;

	friend std::ostream& operator<<(std::ostream& out, const vec3& v);
	friend vec3 operator+(const vec3& u, const vec3& v);
	friend vec3 operator-(const vec3& u, const vec3& v);
	friend vec3 operator*(const vec3& u, const vec3& v);
	friend vec3 operator*(double t, const vec3& v);
	friend vec3 operator*(const vec3& v, double t);
	friend vec3 operator/(const vec3& v, double t);
	friend double dot(const vec3& u, const vec3& v);
	friend vec3 cross(const vec3& u, const vec3& v);
	friend vec3 unit_vector(const vec3& v);
	static vec3 random();
	static vec3 random_in_unit_sphere();
	static vec3 random_unit_vector();
	static vec3 random(double min, double max);
	static vec3 random_in_hemisphere(const vec3& normal);
	static vec3 reflect(const vec3& v, const vec3& n);
	static vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat);
	static vec3 random_in_unit_disk();


private:
	double e[3];
};

using point3 = vec3;
using color = vec3;

#endif