/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:22:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/16 14:18:17 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s_ray
{
	t_point	origin;
	t_point	direction;
}	t_ray;

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

int	main()
{
	t_point		origin = {2, 3, 4};
	t_vector	direction = {1, 0, 0};
	t_ray		r;
	t_point		pos;

	r = ray(origin, direction);
	pos = position(r, 0);
	printf("pos.x = %f\npos.y = %f\npos.z = %f\n", pos.x, pos.y, pos.z);
	pos = position(r, 1);
	printf("pos.x = %f\npos.y = %f\npos.z = %f\n", pos.x, pos.y, pos.z);
	pos = position(r, -1);
	printf("pos.x = %f\npos.y = %f\npos.z = %f\n", pos.x, pos.y, pos.z);
	pos = position(r, 2.5);
	printf("pos.x = %f\npos.y = %f\npos.z = %f\n", pos.x, pos.y, pos.z);
	return (0);
}