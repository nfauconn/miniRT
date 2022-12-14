/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:21:52 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/11 14:01:28 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lights.h"

t_vector	cylinder_normal(t_elem cyl, t_point local_pt)
{
	float		dist;
	t_vector	local_normal;

	dist = (local_pt.x * local_pt.x) + (local_pt.z * local_pt.z);
	if (dist < 1 && local_pt.y >= (cylinder_max(cyl) - EPSILON))
		local_normal = create_vector(0, 1, 0);
	else if (dist < 1 && local_pt.y <= (cylinder_min(cyl) + EPSILON))
		local_normal = create_vector(0, -1, 0);
	else
		local_normal = create_vector(local_pt.x, 0, local_pt.z);
	return (local_normal);
}

/* find the perpendicular vector to sphere at point */
t_vector	normal_at(t_elem *obj, t_point w_pt)
{
	t_point		local_pt;
	t_vector	local_normal;
	t_vector	w_normal;

	local_pt = matrix_tuple_mult(inverse(obj->transform), w_pt);
	if (obj->shape == sphere)
		local_normal = local_pt - obj->o_pos;
	if (obj->shape == plane)
	{
		local_normal = create_vector(0, 1, 0);
		//local_normal = create_vector(obj->o_pos.x, obj->o_pos.y, obj->o_pos.z);
	}
	if (obj->shape == cylinder)
		local_normal = cylinder_normal(*obj, local_pt);
	w_normal = matrix_tuple_mult(transpose(inverse(obj->transform)), local_normal);
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
	light->color = color;
}

t_rgb	lighting(t_scene *scene, t_elem *light, t_inter inter, bool shadowed)
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

//	TRY
/* (void)scene;
	effective_color = inter.obj->material.color * light->color;
	lightv = normalize(light->w_pos - inter.over_point);

	ambient = (t_rgb)BLACK;//inter.obj->material.color * inter.obj->material.ambient;
 */

	//combines the surface color with the light's color/intensity
	effective_color = inter.obj->material.color * light->color;
	//find the direction to the light source
	lightv = normalize(light->w_pos - inter.over_point);
	//compute the ambient contribution
	ambient = effective_color * scene->amblight->color;
	//light_dot_normal represents cosine of angle btw light vec and the normal vec
	light_dot_normal = dot_product(lightv, inter.normalv);
	//a negative number means the light is on the other side of the surface
	if (light_dot_normal < 0)
	{
		diffuse = (t_rgb)BLACK;
		specular = (t_rgb)BLACK;
	}
	else //compute the diffuse contribution
	{
		diffuse = effective_color * inter.obj->material.diffuse * light_dot_normal;
		//reflect_dot_eye represents cos of angle btw reflection vec and eye vec
		reflectv = reflect(-lightv, inter.normalv);
		reflect_dot_eye = dot_product(reflectv, inter.eyev);
		if (reflect_dot_eye <= 0)
			specular = (t_rgb)BLACK;
		else //compute the specular contribution
		{
			factor = pow(reflect_dot_eye, inter.obj->material.shininess);
			specular = light->color * inter.obj->material.specular * factor;
		}
	}
	if (shadowed)
		res = ambient;
	else
		res = ambient + diffuse + specular;//ambient + diffuse + specular;
/* 	res += scene->amblight->color;
	adjust_light(&res); */
	return (res);
}

bool	is_shadowed(t_scene *scene, t_elem *light, t_point	point)
{
	t_vector	v;
	float		distance;
	t_vector	direction;
	t_ray		r;
	t_inter		i;

	v = light->w_pos - point;	// vector from light to point
	distance = length(v);				// distance from light to point
	direction = normalize(v);			// normalized distance
	r = ray(point, direction);
	i = intersect_world(scene, r);		// check if object btw light and point
	if (i.t > 0 && i.t < distance)		// if yes -> shadow
		return (true);
	return (false);
}

/*
to support multiple light sources : iterate over all the light sources,
calling lighting() for each one and adding the colors together
"Be warned, though: adding multiple light sources will slow your renderer down,
especially when you get to Chapter 8, Shadows, on page 109. But if you have CPU
cycles to burn, having more than one light can make some neat effects possible, like
overlapping shadows"
*/


t_rgb	shade_hit(t_scene *world, t_inter inter)
{
	bool	shadowed;
	t_rgb	color;
	t_elem	*light;
/*
//	to make chap7 tests pass:
	shadowed = 0;
	return (lighting(world, world->lights, inter, shadowed));
*/
	if (!world->lights)
	{
		color = inter.obj->material.color * world->amblight->color;
		return (color);
	}
	light = world->lights;
	shadowed = is_shadowed(world, light, inter.over_point);
	color = lighting(world, light, inter, shadowed);
	light = light->next;
 	while (light)
	{
		shadowed = is_shadowed(world, light, inter.over_point);
		color += lighting(world, light, inter, shadowed);
//		adjust_light(&color);
		light = light->next;
	}
	adjust_light(&color);
	return (color);
}

t_point	over_point(t_point ori, t_vector normalv)
{
	t_point	res;

	res = ori + normalv * EPSILON * 200;
	return (res);
}

void	prepare_computations(t_inter *i, t_ray ray)
{
	i->point = position(ray, i->t);
	i->eyev = -ray.dir;
	i->normalv = normal_at(i->obj, i->point);
	if (i->obj->shape != plane && dot_product(i->normalv, i->eyev) < 0)
	{
		i->inside = 1;
		i->normalv = -i->normalv;
	}
	else
		i->inside = 0;
	i->over_point = over_point(i->point, i->normalv);
}

