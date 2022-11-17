#include "minirt.h"

t_bool	hit_sphere(t_float3 center, float radius, t_float3 raydirection, t_scene *scene)
{
	t_float3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	oc = scene->origin - center;
	a = dot3(raydirection, raydirection);
	b = 2.0 * dot3(oc, raydirection);
	c = dot3(oc, oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}
