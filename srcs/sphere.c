#include "minirt.h"

t_bool	hit_sphere(float3 center, float radius, float3 raydirection, t_scene *scene)
{
	float3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	oc = scene->origin - center;
	a = dot(raydirection, raydirection);
	b = 2.0 * dot(oc, raydirection);
	c = dot(oc, oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}
