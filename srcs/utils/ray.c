/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:22:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/14 18:05:26 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "matrix.h"

/* create a ray struct with his origin point & his dest vector */
t_ray	ray(t_point orig, t_vector dest)
{
	t_ray	ray;

	ray.orig = orig;
	ray.dest = dest;
	return (ray);
}

/* position after t iterations of vector r.dest on point r.origin
=>> util for light and shading
--> turning intersections into actual surface informations */
t_point	position(t_ray ray, float t)
{
	return (ray.orig + ray.dest * t);
}


t_inter	intersection(float t, t_elem obj)
{
	t_inter	i;

	i.t = t;
	i.obj = obj;
	return (i);
}

/*  find the intersection that has the lowest nonnegative t value*/
t_inter	hit(t_xs xs)
{
	size_t	i;
	t_inter	hit;

	if (!xs.count)
		hit.t = -1;
	else
	{
		i = 0;
		while (i < xs.count && xs.t[i] < 0)
			i++;
		if (i == xs.count)
			hit.t = -1;
		else
		{
			hit = intersection(xs.t[i], xs.obj);
			while (++i < xs.count)
			{
				if (xs.t[i] >= 0 && xs.t[i] < hit.t)
				hit = intersection(xs.t[i], xs.obj);
			}
		}
	}
	return (hit);
}

/* find inter of the given ray with a sphere */
t_xs	sp_xs(t_elem s, t_ray r)
{
	t_vector	sphere_to_ray;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	t_xs		xs;

	sphere_to_ray = r.orig - s.o_pos;
	a = dot3(r.dest, r.dest);
	b = 2 * dot3(r.dest, sphere_to_ray);
	c = dot3(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		ft_bzero(&xs, sizeof(xs));
	else
	{
		xs.count = 2;
		xs.t[0] = (-b - sqrt(discriminant)) / (2 * a);
		xs.t[1] = (-b + sqrt(discriminant)) / (2 * a);
	}
	return (xs);
}

t_ray	transform_ray(t_ray prev_r, t_m4x4_f matrix)
{
	t_ray	r;

	r.orig = matrix_tuple_mult(matrix, prev_r.orig);
	r.dest = matrix_tuple_mult(matrix, prev_r.dest);
	return (r);
}

void	set_transform(t_elem *obj, t_m4x4_f transfo_matrix)
{
	obj->transform = transfo_matrix;
}

/* INTERSECT
** create a struct containing all intersections of a ray with a given obj
** (sphere can only have 2 but maybe more are needed for other objects) */
t_xs	intersect(t_elem obj, t_ray r)
{
	t_xs	xs;

	r = transform_ray(r, inverse(obj.transform));
	//obj_to_ray ?? cf sp_xs !!!!!!!!!!!!!!!!!!!!!!!
	if (obj.id.shape == sphere)
		xs = sp_xs(obj, r);
	else
		ft_bzero(&xs, sizeof(xs));
	xs.obj = obj;
	return (xs);
}
