/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:22:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/16 13:38:22 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "matrix.h"

/* create a ray struct with his origin point & his dest vector */
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

t_ray	transform_ray(t_ray prev_r, t_m4x4_f matrix)
{
	t_ray	r;

	r.orig = matrix_tuple_mult(matrix, prev_r.orig);
	r.dest = matrix_tuple_mult(matrix, prev_r.dest);
	return (r);
}

void	set_transform(t_elem *obj, t_m4x4_f transfo_matrix)
{
	obj->transform = transfo_matrix;
}

