/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:44:24 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2022/12/17 15:22:15 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inter.h"

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
t_xs	sp_intersect(t_elem s, t_ray r)
{
	t_vector	sphere_to_ray;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	t_xs		xs;

	sphere_to_ray = r.orig - s.o_pos;
	a = dot3(r.dir, r.dir);
	b = 2 * dot3(r.dir, sphere_to_ray);
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

t_xs	pl_intersect(t_elem p, t_ray r)
{
	t_xs	xs;

	(void)p;
	if (fabsf(r.dir.y) < EPSILON)
		xs.count = 0;
	else
	{
		xs.count = 1;
		xs.t[0] = -r.orig.y / r.dir.y;
	}
	return (xs);
}

/* INTERSECT
** create a struct containing all intersections of a ray with a given obj
** (sphere can only have 2 but maybe more are needed for other objects) */
t_xs	intersect(t_elem obj, t_ray r)
{
	t_xs	xs;

	r = transform_ray(r, inverse(obj.transform));
	//obj_to_ray ?? cf sp_intersect !!!!!!!!!!!!!!!!!!!!!!!
	if (obj.id.shape == sphere)
		xs = sp_intersect(obj, r);
	else if (obj.id.shape == plane)
		xs = pl_intersect(obj, r);
	else
		xs.count = 0;
	xs.obj = obj;
	return (xs);
}

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
