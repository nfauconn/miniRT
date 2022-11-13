/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:38:22 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/13 19:12:28 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	dot(float3 vector1, float3 vector2)
{
	return ((vector1.x * vector2.x) \
		+ (vector1.y * vector2.y) \
		+ (vector1.z * vector2.z));
}

float magnitude(float3 vector)
{
	float res;

	res = sqrt(dot(vector, vector));
	return (res);
}

float3	unit_direction(float3 vector)
{
	float3	res;

	res = vector / magnitude(vector);
	return (res);
}
