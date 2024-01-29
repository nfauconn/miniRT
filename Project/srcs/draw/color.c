/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:40:49 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/14 14:26:55 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_rgb	create_color(float red, float green, float blue)
{
	t_rgb	color;

	color.x = red;
	color.y = green;
	color.z = blue;
	color.w = 0;
	return (color);
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
	i->over_point = i->point + i->normalv * EPSILON * 200;
}

/* intersect the world with the given ray
and return the color at the given intersection */
t_rgb	color_at(t_scene *world, t_ray ray)
{
	bool	is_void;
	t_inter	i;
	t_rgb	color;

	if (!world->objs)
		is_void = 1;
	else
	{
		is_void = 0;
		i = intersect_world(world, ray);
	}
	if (is_void || i.t <= 0)
	{
		color = create_color(0, 0, 0);
		return (color);
	}
	prepare_computations(&i, ray);
	color = shade_hit(world, i);
	return (color);
}
