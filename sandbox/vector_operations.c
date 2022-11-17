/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:38:22 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/16 12:03:11 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	dot(t_float3 vector1, t_float3 vector2)
{
	return ((vector1.x * vector2.x) \
		+ (vector1.y * vector2.y) \
		+ (vector1.z * vector2.z));
}

float magnitude(t_float3 vector)
{
	float res;

	res = sqrt(dot(vector, vector));
	return (res);
}

t_float3	unit_direction(t_float3 vector)
{
	t_float3	res;

	res = vector / magnitude(vector);
	return (res);
}
