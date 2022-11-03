#include "minirt.h"

bool	hit_sphere(float3 center, float radius, float3 raydirection, t_scene scene)
{
	float3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	oc = scene.origin - center;
	a = addition_of_elements_multiplication(raydirection, raydirection);
	b = 2.0 * addition_of_elements_multiplication(oc, raydirection);
	c = addition_of_elements_multiplication(oc, oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}
