/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:34:33 by rokerjea          #+#    #+#             */
/*   Updated: 2022/11/12 18:23:05 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdio.h>
#include <errno.h>

typedef float	t_float4	__attribute__((ext_vector_type(4)));
typedef int		t_int4	__attribute__((ext_vector_type(4)));

int	is_equal(float x, float y)
{
	if (x == y)
		return (1);
	return (0);
}

t_bool	is_point(t_float4 tuple)
{
	if (tuple.w == 1.0)
		return (1);
	return (0);
}

t_bool	is_vector(t_float4 tuple)
{
	if (tuple.w == 1.0)
		return (0);
	return (1);
}

bool	same_tuple(t_float4 tup1, t_float4 tup2)
{
	float	epsilon;

	epsilon = 0.00001;
	if (fabs(tup1.x - tup2.x) > epsilon || fabs(tup1.y - tup2.y) > epsilon
		|| fabs(tup1.z - tup2.z) > epsilon || fabs(tup1.w - tup2.w) > epsilon)
		return (0);
	return (1);
}

bool	tuple_bool(t_int4 tuple)
{
	if (tuple.x == 0 || tuple.y == 0 || tuple.z == 0 || tuple.w == 0)
		return (0);
	return (1);
}

float	addition_of_squared_elements(t_float4 vector)
{
	return ((vector.x * vector.x) \
		+ (vector.y * vector.y) \
		+ (vector.z * vector.z) \
		+ (vector.w * vector.w));
}

float	length(t_float4 vector)
{
	float	res;

	res = sqrt(addition_of_squared_elements(vector));
	return (res);
}

bool	same_float(float f1, float f2)
{
	float	epsilon;

	epsilon = 0.00001;
	if (fabs(f1 - f2) > epsilon)
		return (0);
	return (1);
}

t_float4	unit_direction(t_float4 vector)
{
	t_float4	res;

	res = vector / length(vector);
	return (res);
}

float	dot_product(t_float4 tup1, t_float4 tup2)
{
	return ((tup1.x * tup2.x) \
		+ (tup1.y * tup2.y) \
		+ (tup1.z * tup2.z) \
		+ (tup1.w * tup2.w));
}

t_float4	cross_product(t_float4 tup1, t_float4 tup2)
{
	t_float4	res;

	res.x = tup1.y * tup2.z - tup1.z * tup2.y;
	res.y = tup1.z * tup2.x - tup1.x * tup2.z;
	res.z = tup1.x * tup2.y - tup1.y * tup2.x;
	res.w = 0;
	return (res);
}
