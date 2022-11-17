/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:22:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/17 17:13:37 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s_ray
{
	t_point	orig;
	t_point	dest;
}	t_ray;

typedef struct s_intersection
{
	size_t	count;
	float	pos[2];
}	t_intersect;


typedef struct s_sphere
{
	ssize_t	id;
	t_point	center;
}	t_sphere;

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

// find the position of a point of the ray at distance t (t is for time, as : distance = ray size * t = 1 * t =>> util for light and shading --> turning intersections into actual surface informations
t_point	position(t_ray ray, float t)
{
	return (ray.orig + ray.dest * t);
}

/* // r.orig{0, 0, -5} + r.dest * t = {0, 0, -1} <=> r.orig.z + r.dest * t = sphere.z <=> r.dest * t = sphere.z - r.orig.z <=> t = (-1 - r.orig.z) / r.dest.z
t_intersect	intersect(t_sphere s, t_ray r)
{
	t_intersect	xs;
	t_point		pos;
	float		t;

	(void)sphere;
	if ((r.orig.z < 0 && r.dest.z < 0)
		|| (r.orig.z > 0 && r.dest.z > 0))
		return (set_xs(0, 0, 0));
	t = -r.orig.z / r.dest.z; //to find what is t for position.z = 0
	pos = position(r, t);
	if (same_tuple(pos, s.center))
	{
		xs.count = 2;
		xs.pos[0] = (-1 - r.orig.z) / r.dest.z;
		xs.pos[1] = (1 - r.orig.z) / r.dest.z;
	}
	else
		return (set_xs(0, 0, 0));
	return (xs);
}
 */
// r.orig{0, 1, -5} + r.dest.z * ? = tangente{0, 1, 0} <=> r.dest.z * ? = 0 - r.orig.z <=> ? = (0 -r.orig.z) / r.dest.z
/* t_intersect	tangent_sp_intersect(t_sphere sphere, t_ray r)
{
	t_intersect	xs;

	(void)sphere;
	xs.count = 2;
	xs.pos[0] = -r.orig.z / r.dest.z;
	xs.pos[1] = xs.pos[0];
	return (xs);
}
	if ((r.orig.z < 0 && r.dest.z <= 0)
		|| (r.orig.z > 0 && r.dest.z >= 0)
		|| (r.dest.z == 0 && !same_tuple(r.orig, s.center)))
		return (set_xs(0, 0, 0));
	if (same_tuple(r.orig, s.center))
		t = 0;
	else
		t = -r.orig.z / r.dest.z; //to find what is t for position.z = 0
	pos = position(r, t);
 */

t_intersect	set_xs(float discriminant, float a, float b)
{
	t_intersect	xs;

	if (discriminant < 0)
	{
		xs.count = 0;
		xs.pos[0] = 0;
		xs.pos[1] = 0;
	}
	else
	{
		xs.count = 2;
		xs.pos[0] = (-b - sqrt(discriminant)) / (2 * a);
		xs.pos[1] = (-b + sqrt(discriminant)) / (2 * a);
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
	xs = set_xs(discriminant, a, b);
	return (xs);
}

int	main()
{
	t_point		orig = {0, 1, -5};
	t_vector	dest = {0, 0, 1};
	t_ray		r;
	t_sphere		s;
	t_intersect	xs;

	r = ray(orig, dest);
	s = sphere_id();
	xs = intersect(s, r);
	return (0);
}