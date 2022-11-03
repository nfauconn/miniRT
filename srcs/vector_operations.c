/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:38:22 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/03 17:00:10 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	addition_of_elements_multiplication(float3 vector1, float3 vector2)
{
	return ((vector1.x * vector2.x) \
		+ (vector1.y * vector2.y) \
		+ (vector1.z * vector2.z));
}

float addition_of_squared_elements(float3 vector)
{
	return ((vector.x * vector.x) \
		+ (vector.y * vector.y) \
		+ (vector.z * vector.z));
}

float length(float3 vector)
{
	float res;

	res = sqrt(addition_of_squared_elements(vector));
	return (res);
}

float3	unit_direction(float3 vector)
{
	float3	res;

	res = vector / length(vector);
	return (res);
}
