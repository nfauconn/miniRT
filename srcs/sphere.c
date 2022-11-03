#include "miniRT.h"

bool	hit_sphere(double3 center, double radius, double3 raydirection, t_scene scene)
{
	double3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = scene.origin - center;
	a = addition_of_elements_multiplication(raydirection, raydirection);
	b = 2.0 * addition_of_elements_multiplication(oc, raydirection);
	c = addition_of_elements_multiplication(oc, oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}
