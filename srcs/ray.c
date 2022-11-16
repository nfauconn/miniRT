/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:22:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/16 19:30:40 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	dot3(t_float3 tup1, t_float3 tup2)
{
	return ((tup1.x * tup2.x) \
		+ (tup1.y * tup2.y) \
		+ (tup1.z * tup2.z));
}

typedef struct s_ray
{
	t_point	origin;
	t_point	direction;
}	t_ray;

typedef struct s_intersection
{
	size_t	count;
	float	pos[2];
}	t_intersect;

t_ray	ray(t_point origin, t_vector direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

// find the position of a point of the ray at distance t (t is for time, as :
//														distance = ray size * t
//	util for light and shading									 = 1 * t
//	--> turning intersections into actual surface informations
t_point	position(t_ray ray, float t)
{
	return (ray.origin + ray.direction * t);
}

// r.origin{0, 0, -5} + r.dir * t = {0, 0, -1}
// r.origin.z + r.dir * t = sphere.z
// r.dir * t = sphere.z - r.origin.z
// t = (-1 - r.origin.z) / r.dir.z
t_intersect	center_sp_intersect(ssize_t sphere, t_ray r)
{
	t_intersect	xs;

	(void)sphere;
	xs.count = 2;
	xs.pos[0] = (-1 - r.origin.z) / r.direction.z;
	xs.pos[1] = (1 - r.origin.z) / r.direction.z;
	return (xs);
}
// /!\ as sphere will always touch {0, 1, 0}, make a more general func?

// r.origin{0, 1, -5} + r.direction.z * ? = tangente{0, 1, 0}
// r.dir.z * ? = 0 - r.origin.z
// ? = (0 -r.origin.z) / r.dir.z
t_intersect	tangent_sp_intersect(ssize_t sphere, t_ray r)
{
	t_intersect	xs;

	(void)sphere;
	xs.count = 2;
	xs.pos[0] = -r.origin.z / r.direction.z;
	xs.pos[1] = xs.pos[0];
	return (xs);
}
// /!\ as sphere will always touch {0, 1, 0}, make a more general func?

ssize_t	sphere_id()
{
	static ssize_t	id = -1;

	id++;
	return(id);
}

t_bool	hit_sp(ssize_t sphere, t_ray r)
{
	t_vector	sphere_to_ray;
	float		a;
	float		b;
	float		c;
	float		discriminant;

	(void)sphere;
	sphere_to_ray = r.origin - (t_point){0, 0, 0};
	a = dot3(r.direction, r.direction);
	b = 2 * dot3(r.direction, sphere_to_ray);
	c = dot3(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = b * b - 4 * a *c;
	return (discriminant >= 0);
}


int	main()
{
	t_point		origin = {6, 5, 5};
	t_vector	direction = {9, 9, 9};
	t_ray		r;
	ssize_t		s;
	t_intersect	xs;

	r = ray(origin, direction);
	s = sphere_id();
	xs = center_sp_intersect(s, r);
	xs = tangent_sp_intersect(s, r);
	if (hit_sp(s, r))
		printf("youpi\n"); // seems to be wrong
	return (0);
}