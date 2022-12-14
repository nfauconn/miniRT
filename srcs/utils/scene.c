/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:04:15 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/14 19:26:03 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/* find hits of objects
RETURN PEUT ETRE NEG OU 0 !! CHECKER
parcourir liste chainee d objets : */
t_inter	intersect_world(t_scene *world, t_ray ray)
{
	t_elem		*obj;
	t_xs		xs;
	t_inter		i;
	t_inter		res;

	obj = world->objs;
	xs = intersect(*obj, ray);
	i = hit(xs);
	res = i;
	obj = obj->next;
	while (obj)
	{
		xs = intersect(*obj, ray);
		i = hit(xs);
		if (i.t > 0 && (i.t < res.t || res.t < 0))
			res = i;
		obj = obj->next;
	}
	return (res);
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
	i->eyev = -ray.dest;
	i->normalv = normal_at(&i->obj, i->point);
	if (dot_product(i->normalv, i->eyev) < 0)
	{
		i->inside = 1;
		i->normalv = -i->normalv;
	}
	else
		i->inside = 0;
	i->over_point = over_point(i->point, i->normalv);
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
shadowed = 0;
//	shadowed = is_shadowed(world, inter.over_point);
//	return (lighting(inter.obj.material, world->lights, inter.over_point, inter.eyev, inter.normalv, shadowed));
	return (lighting(inter.obj.material, world->lights, inter.point, inter.eyev, inter.normalv, shadowed));
}

t_m4x4_f	view_transform(t_point from, t_point to, t_point up)
{
	t_m4x4_f	res;
	t_vector	forward;
	t_vector	upn;
	t_vector	left;
	t_vector	true_up;

	forward = normalize(to - from);
	upn = normalize(up);
	left = cross_product(forward, upn);
	true_up = cross_product(left, forward);
	res = identity_matr();
	res[0][0] = left.x;
	res[0][1] = left.y;
	res[0][2] = left.z;
	res[1][0] = true_up.x;
	res[1][1] = true_up.y;
	res[1][2] = true_up.z;
	res[2][0] = -forward.x;
	res[2][1] = -forward.y;
	res[2][2] = -forward.z;
	return (matrix_mult(res, translation(-from.x, -from.y, -from.z)));
}

t_ray	ray_for_pixel(t_camera cam, float px, float py)
{
	float	x_offset;
	float	y_offset;
	float	world_x;
	float	world_y;

	x_offset = (px + 0.5) * cam.pixel_size;
	y_offset = (py + 0.5) * cam.pixel_size;
	world_x = cam.half_width - x_offset;
	world_y = cam.half_height - y_offset;

	t_ray	res;
	t_float4	pixel;
	pixel = matrix_tuple_mult(inverse(cam.transform), create_point(world_x, world_y, -1));
	res.orig = matrix_tuple_mult(inverse(cam.transform), create_point(0, 0, 0));
	res.dest = normalize(pixel - res.orig);
	return (res);
}
