/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:22:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/17 15:05:18 by nfauconn         ###   ########.fr       */
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


ssize_t	sphere_id()
{
	static ssize_t	id = -1;

	id++;
	return(id);
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

t_intersect	set_xs(size_t count, float pos1, float pos2)
{
	t_intersect	xs;

	xs.count = count;
	xs.pos[0] = pos1;
	xs.pos[1] = pos2;
	return (xs);
}

// r.orig{0, 0, -5} + r.dir * t = {0, 0, -1} <=> r.orig.z + r.dir * t = sphere.z <=> r.dir * t = sphere.z - r.orig.z <=> t = (-1 - r.orig.z) / r.dir.z
t_intersect	intersect(ssize_t sphere, t_ray r)
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
	if (same_tuple(pos, (t_point){0, 0, 0}))
	{
		xs.count = 2;
		xs.pos[0] = (-1 - r.orig.z) / r.dest.z;
		xs.pos[1] = (1 - r.orig.z) / r.dest.z;
	}
	else
		return (set_xs(0, 0, 0));
	return (xs);
}

// r.orig{0, 1, -5} + r.dest.z * ? = tangente{0, 1, 0} <=> r.dir.z * ? = 0 - r.orig.z <=> ? = (0 -r.orig.z) / r.dir.z
/* t_intersect	tangent_sp_intersect(ssize_t sphere, t_ray r)
{
	t_intersect	xs;

	(void)sphere;
	xs.count = 2;
	xs.pos[0] = -r.orig.z / r.dest.z;
	xs.pos[1] = xs.pos[0];
	return (xs);
} */

int	main()
{
	t_point		orig = {0, 1, -5};
	t_vector	dest = {0, 0, 1};
	t_ray		r;
	ssize_t		s;
	t_intersect	xs;

	r = ray(orig, dest);
	s = sphere_id();
	xs = intersect(s, r);
//	xs = tangent_sp_intersect(s, r);
	return (0);
}