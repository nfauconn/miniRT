#include "lights.h"

/* find the perpendicular vector to sphere at point */
t_vector	normal_atsphere(t_elem *sp, t_point world_pt)
{
	t_point		o_pt;
	t_vector	o_normal;
	t_vector	w_normal;

	o_pt = matrix_tuple_mult(inverse(sp->transform), world_pt);
	o_normal = o_pt - sp->o_pos;
	w_normal = matrix_tuple_mult(transpose(inverse(sp->transform)), o_normal);
	w_normal.w = 0;
	return (normalize(w_normal));
}

/* find the result of reflecting the in vector around the normal vector */
t_vector	reflect(t_vector in, t_vector normal)
{
	t_vector	reflect;

	reflect = in - normal * 2 * dot_product(in, normal);
	return (reflect);
}

/* ID PARSING : diviser en 1 func set point et une func set light */
void	point_light(t_elem *light, t_point pos, float ratio)
{
	light->w_pos = pos;
	light->specs.intensity.f = ratio;
	light->specs.intensity.f4 = create_point(ratio, ratio, ratio);
}

t_material	default_material()
{
	t_material	material;

	material.color = (t_rgb){1, 1, 1, 0};
	material.ambiant = 0.1;
	material.diffuse = 0.9;
	material.specular = 0.9;
	material.shininess = 200.0;
	return (material);
}

t_rgb	lighting(t_material m, t_elem light, t_point pos, t_vector eyev, t_vector normalv)
{

}