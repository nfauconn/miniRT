/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:44:24 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/11 14:01:28 by nfauconn         ###   ########.fr       */
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

float	cylinder_min(t_elem cyl)
{
	float	min;

	min = 0 + cyl.w_pos.y;;
	// min = matrix_tuple_mult(cyl.transform, create_point(0, -0.5, 0));
	// printf("min. x,y,z = %f, %f, %f\n", min.x, min.y, min.z);
	return (min);
}

float	cylinder_max(t_elem cyl)
{
	float	max;

	// max = matrix_tuple_mult(cyl.transform, create_point(0, 0.5, 0));
	max = cyl.specs.diam_hght[1] + cyl.w_pos.y;
	return (max);
}

t_xs	cylinder_limits(t_elem cyl, t_ray ray, t_xs xs)
{
	float	ymin;
	float	ymax;
	float	y0;
	float	y1;

	ymax = cylinder_max(cyl);
	ymin = cylinder_min(cyl);
	// printf("max = %f, min = %f\n", ymax, ymin);
	y0 = ray.orig.y + (xs.t[0] * ray.dir.y);
	if (y0 <= ymin || y0 >= ymax)
	{
		xs.count--;
		xs.t[0] = xs.t[1];
	}
	y1 = ray.orig.y + (xs.t[1] * ray.dir.y);
	if (y1 <= ymin || y1 >= ymax)
	{
		xs.count--;
		xs.t[1] = -1;
	}
	return (xs);
}

int	check_cap(t_ray r, int t)
{
	int	x;
	int	z;

	x = r.orig.x + (t * r.dir.x);
	z = r.orig.z + (t * r.dir.z);
	return((x * x + z * z) <= 1);
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

t_xs	intersect_cyl_caps(t_elem cyl, t_ray r, t_xs xs)
{
	int	t;

	if (r.dir.y < EPSILON && r.dir.y > -EPSILON)
		return (xs);
	t = (cylinder_min(cyl) - r.orig.y) / r.dir.y;
	if (check_cap(r, t))
		xs = add_t_to_xs(xs, t);
	t = (cylinder_max(cyl) - r.orig.y) / r.dir.y;
	if (check_cap(r, t))
		xs = add_t_to_xs(xs, t);
	return (xs);
}

t_xs	local_intersect_cyl(t_elem cyl, t_ray ray)
{
	t_xs	xs;
	float	a;
	float	b;
	float	c;
	float	disc;

	a = (ray.dir.x * ray.dir.x) + (ray.dir.z * ray.dir.z);
	b = (2 * ray.orig.x * ray.dir.x) + (2 * ray.orig.z * ray.dir.z);
	c = (ray.orig.x * ray.orig.x) + (ray.orig.z * ray.orig.z) - 1;
	disc = (b * b) - (4 * a * c);
	if (disc < 0 || (a > -0.001 && a < 0.001))
		ft_bzero(&xs, sizeof(xs));
	else
	{
		xs.count = 2;
		xs.t[0] = (-b -sqrt(disc)) / (2 * a);
		xs.t[1] = (-b +sqrt(disc)) / (2 * a);
		if (xs.t[0] > xs.t[1])
		{
			c = xs.t[0];
			xs.t[0] = xs.t[1];
			xs.t[1] = c;
		}
		xs = cylinder_limits(cyl, ray, xs);
	}
	// if (xs.count < 2)
	// 	xs = intersect_cyl_caps(cyl, ray, xs);
	return (xs);
}
/* INTERSECT
** create a struct containing all intersections of a ray with a given obj
** (sphere can only have 2 but maybe more are needed for other objects) */
t_xs	intersect(t_elem *obj, t_ray r)
{
	t_xs	xs;

	r = transform_ray(r, inverse(obj->transform));
	//obj_to_ray ?? cf sp_intersect !!!!!!!!!!!!!!!!!!!!!!!
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
