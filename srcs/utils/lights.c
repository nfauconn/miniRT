#include "lights.h"

t_rgb	create_color(float red, float green, float blue)
{
	t_rgb	color;

	color.x = red;
	color.y = green;
	color.z = blue;
	color.w = 0;
	return (color);
}

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
void	point_light(t_elem *light, t_point pos, t_rgb color)//A MON AVIS ON VA POUVOIR SUPPR LE F4 CAR TJRS LES 4MEMES VALEURS (UTILISE SANS DOUTE CA POUR SIOMPLIFIER CALCULS)
{
	light->w_pos = pos;
	light->color = color; //light->intensity dans son jargon
	//A REFACTO ABSOLU<EMT avec le parsing
}

t_rgb	lighting(t_material m, t_elem *light, t_point pos, t_vector eyev, \
												t_vector normalv, bool in_shadow)
{
	t_rgb		effective_color;
	t_vector	reflectv;
	float		reflect_dot_eye;
	t_vector	lightv;
	float		light_dot_normal;
	t_rgb		ambient;
	t_rgb		diffuse;
	t_rgb		specular;
	t_rgb		res;
	float		factor;

	effective_color = m.color * light->color;
	lightv = normalize(light->w_pos - pos);
	ambient = effective_color * m.ambient;
	light_dot_normal = dot_product(lightv, normalv);
	if (light_dot_normal < 0)
	{
		diffuse = (t_rgb)BLACK;
		specular = (t_rgb)BLACK;
	}
	else
	{
		diffuse = effective_color * m.diffuse * light_dot_normal;
		reflectv = reflect(-lightv, normalv);
		reflect_dot_eye = dot_product(reflectv, eyev);
		if (reflect_dot_eye <= 0)
			specular = (t_rgb)BLACK;
		else
		{
			factor = pow(reflect_dot_eye, m.shininess);
			specular = light->color * m.specular * factor;
		}
	}
	if (in_shadow)
		res = ambient;
	else
		res = ambient + diffuse + specular;
	return (res);
}

bool	is_shadowed(t_scene *scene, t_point	point)
{
	t_vector	v;
	float		distance;
	float		direction;
	t_ray		r;
	t_inter		i;

	v = scene->lights->w_pos - point;
	distance = magnitude(v);
	direction = normalize(v);
	r = ray(point, direction);
	i = intersect_world(scene, r);
	if (i.t > 0 && i.t < distance)
		return (true);
	return (false);
}