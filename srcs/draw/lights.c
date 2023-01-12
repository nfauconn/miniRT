/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:21:52 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/12 16:1 by fjeiwjifeoh      ###   ########.fr       */
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

t_vector	normal_at(t_elem *obj, t_point w_pt)
{
	t_point		local_pt;
	t_vector	local_normal;
	t_vector	w_normal;

	local_pt = matrix_tuple_mult(inverse(obj->transform), w_pt);
	if (obj->shape == sphere)
		local_normal = local_pt - obj->o_pos;
	if (obj->shape == plane)
		local_normal = create_vector(0, 1, 0);
	if (obj->shape == cylinder)
		local_normal = cylinder_normal(*obj, local_pt);
	w_normal = matrix_tuple_mult(transpose(inverse(obj->transform)), \
																local_normal);
	w_normal.w = 0;
	return (normalize(w_normal));
}

t_vector	reflect(t_vector in, t_vector normal)
{
	t_vector	reflect;

	reflect = in - normal * 2 * dot_product(in, normal);
	return (reflect);
}

void	point_light(t_elem *light, t_point pos, t_rgb color)
{
	light->w_pos = pos;
	light->color = color;
}

typedef struct s_lighting
{
	t_rgb		effective_color;
	t_vector	reflectv;
	float		cos_reflectv_eyev;
	t_vector	lightv;
	float		cos_lightv_normalv;
	t_rgb		ambient;
	t_rgb		diffuse;
	t_rgb		specular;
	float		factor;
}	t_lighting;

void	compute_diffuse(t_lighting *l, t_inter inter)
{
	l->diffuse = l->effective_color * inter.obj->material.diffuse \
														* l->cos_lightv_normalv;
	l->reflectv = reflect(-l->lightv, inter.normalv);
	l->cos_reflectv_eyev = dot_product(l->reflectv, inter.eyev);
}

void	compute_specular(t_lighting *l, t_inter inter, t_elem *light)
{
	l->factor = pow(l->cos_reflectv_eyev, inter.obj->material.shininess);
	l->specular = light->color * inter.obj->material.specular * l->factor;
}

void	compute_ambient(t_lighting *l, t_inter inter, t_elem *light, t_scene *s)
{
	l->effective_color = inter.obj->material.color * light->color;
	l->lightv = normalize(light->w_pos - inter.over_point);
	l->ambient = l->effective_color * s->amblight->color;
	l->cos_lightv_normalv = dot_product(l->lightv, inter.normalv);
}

t_rgb	lighting(t_scene *scene, t_elem *light, t_inter inter, bool shadowed)
{
	t_rgb		res;
	t_lighting	l;

	ft_bzero(&l, sizeof (t_lighting));
	compute_ambient(&l, inter, light, scene);
	if (l.cos_lightv_normalv >= 0)
	{
		compute_diffuse(&l, inter);
		if (l.cos_reflectv_eyev > 0)
			compute_specular(&l, inter, light);
	}
	if (shadowed)
		res = l.ambient;
	else
		res = l.ambient + l.diffuse + l.specular;
	return (res);
}

bool	is_shadowed(t_scene *scene, t_elem *light, t_point	point)
{
	t_vector	v;
	float		distance;
	t_vector	direction;
	t_ray		r;
	t_inter		i;

	v = light->w_pos - point;
	distance = length(v);
	direction = normalize(v);
	r = ray(point, direction);
	i = intersect_world(scene, r);
	if (i.t > 0 && i.t < distance)
		return (true);
	return (false);
}

t_rgb	shade_hit(t_scene *world, t_inter inter)
{
	bool	shadowed;
	t_rgb	color;
	t_elem	*light;

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
