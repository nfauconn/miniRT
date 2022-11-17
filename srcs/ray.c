/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:22:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/17 17:53:34 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s_ray
{
	t_point		orig;
	t_point		dest;
}	t_ray;

typedef struct s_sphere
{
	ssize_t		id;
	t_point		center;
}	t_sphere;

typedef struct s_intersection
{
	size_t		count;
	float		t1;
	float		t2;
	t_sphere	s;
}	t_intersect;

t_sphere	sphere_id()
{
	t_sphere		s;
	static ssize_t	id = -1;

	id++;
	s.id = id;
	s.center = (t_point){0, 0, 0};
	return(s);
}

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

t_intersect	set_xs(t_sphere s, float discriminant, float a, float b)
{
	t_intersect	xs;

	xs.s = s;
	if (discriminant < 0)
	{
		xs.count = 0;
		xs.t1 = 0;
		xs.t2 = 0;
	}
	else
	{
		xs.count = 2;
		xs.t1 = (-b - sqrt(discriminant)) / (2 * a);
		xs.t2 = (-b + sqrt(discriminant)) / (2 * a);
	}
	return (xs);
}

t_intersect	intersect(t_sphere s, t_ray r)
{
	t_intersect	xs;
	t_vector	sphere_to_ray;
	float		a;
	float		b;
	float		c;
	float		discriminant;

	sphere_to_ray = r.orig - s.center;
	a = dot3(r.dest, r.dest);
	b = 2 * dot3(r.dest, sphere_to_ray);
	c = dot3(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = pow(b, 2) - 4 * a * c;
	xs = set_xs(s, discriminant, a, b);
	return (xs);
}

int	main()
{
	t_point		orig = {0, 0, 5};
	t_vector	dest = {0, 0, 1};
	t_ray		r;
	t_sphere	s;
	t_sphere	s1;
	t_sphere	s2;
	t_intersect	xs;

	r = ray(orig, dest);
	s = sphere_id();
	s1 = sphere_id();
	s2 = sphere_id();
	xs = intersect(s, r);
	xs = intersect(s1, r);
	xs = intersect(s2, r);
	return (0);
}