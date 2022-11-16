/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:22:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/16 19:00:11 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

ssize_t	sphere_id()
{
	static ssize_t	id = -1;

	id++;
	return(id);
}

int	main()dd
{
	t_point		origin = {0, 0, -5};
	t_vector	direction = {0, 0, 1};
	t_ray		r;
	ssize_t		s;
	t_intersect	xs;

	r = ray(origin, direction);
	s = sphere_id();
	xs = center_intersect(s, r);
	xs = tangent_intersect(s, r);
	return (0);
}