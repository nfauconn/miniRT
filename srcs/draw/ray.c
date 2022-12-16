/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:22:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/16 18:44:50 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "matrix.h"

/* create a ray struct with his origin point & his dir vector */
t_ray	ray(t_point orig, t_vector dir)
{
	t_ray	ray;

	ray.orig = orig;
	ray.dir = dir;
	return (ray);
}

/* position after t iterations of vector r.dir on point r.origin
=>> util for light and shading
--> turning intersections into actual surface informations */
t_point	position(t_ray ray, float t)
{
	return (ray.orig + ray.dir * t);
}

t_ray	transform_ray(t_ray prev_r, t_m4x4_f matrix)
{
	t_ray	r;

	r.orig = matrix_tuple_mult(matrix, prev_r.orig);
	r.dir = matrix_tuple_mult(matrix, prev_r.dir);
	return (r);
}

void	set_transform(t_elem *obj, t_m4x4_f transfo_matrix)
{
	obj->transform = transfo_matrix;
}

