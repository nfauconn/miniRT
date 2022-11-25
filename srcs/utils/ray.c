/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:22:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/25 19:43:32 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "matrix.h"

/* find inter of the given ray with a sphere */
t_xs	sp_xs(t_obj s, t_ray r)
{
	t_vector	sphere_to_ray;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	t_xs		xs;

	sphere_to_ray = r.orig - s.center;
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

t_obj	set_transform(t_obj obj, t_m4x4_f transfo_matrix)
{
	obj.transform = transfo_matrix;
	return (obj);
}

/* INTERSECT
** create a struct containing all intersections of a ray with a given obj
** (sphere can only have 2 but maybe more are needed for other objects) */
t_xs	intersect(t_obj obj, t_ray r)
{
	t_xs	xs;

	r = transform_ray(r, inversion(obj.transform));
	ft_bzero(&xs, sizeof(xs));
	if (obj.id == sphere)
		xs = sp_xs(obj, r);
	xs.obj = obj;
	return (xs);
}

/* add to interlst the new t values found with the given ray
   does not ignore negative t values, as it seems util for chapter 9
   with boolean operations */
void	add_obj_inters(t_obj obj, t_ray r, t_inter **interlst)
{
	size_t				i;
	t_xs	xs;
	t_inter				*inter;

	xs = intersect(obj, r);
	i = 0;
	while (i < xs.count)
	{
		inter = create_inter(xs.t[i], obj);
		interaddback(interlst, inter);
		i++;
	}
}

/*  find the intersection that has the lowest nonnegative t value*/
t_inter	*find_hit(t_inter **interlst)
{
	t_inter	*tmp;
	t_inter	*hit;

	tmp = *interlst;
	hit = tmp;
	while (tmp)
	{
		if (tmp->t >= 0 && tmp->t < hit->t)
			hit = tmp;
		tmp = tmp->next;
	}
	if (hit->t < 0)
		return (NULL);
	return (hit);
}
