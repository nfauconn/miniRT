/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:44:24 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/13 15:46:54 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inter.h"

t_inter	intersection(float t, t_elem *obj)
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

t_xs	add_t_to_xs(t_xs xs, int t)
{
	if (xs.count == 0)
	{
		xs.t[0] = t;
		xs.count++;
	}
	else if (xs.count == 1)
	{
		xs.t[1] = t;
		xs.count++;
	}
	return (xs);
}

/* INTERSECT
** create a struct containing all intersections of a ray with a given obj
** (sphere can only have 2 but maybe more are needed for other objects) */
t_xs	intersect(t_elem *obj, t_ray r)
{
	t_xs	xs;

	r = transform_ray(r, inverse(obj->transform));
	if (obj->shape == sphere)
		xs = sp_intersect(*obj, r);
	else if (obj->shape == plane)
		xs = pl_intersect(*obj, r);
	else if (obj->shape == cylinder)
		xs = local_intersect_cyl(*obj, r);
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
	xs = intersect(obj, ray);
	i = hit(xs);
	res = i;
	obj = obj->next;
	while (obj)
	{
		xs = intersect(obj, ray);
		i = hit(xs);
		if (i.t > 0 && (i.t < res.t || res.t < 0))
			res = i;
		obj = obj->next;
	}
	return (res);
}
