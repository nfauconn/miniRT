/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:38:22 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/03 14:48:06 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	addition_of_elements_multiplication(double3 vector1, double3 vector2)
{
	return ((vector1.x * vector2.x) \
		+ (vector1.y * vector2.y) \
		+ (vector1.z * vector2.z));
}

double addition_of_squared_elements(double3 vector)
{
	return ((vector.x * vector.x) \
		+ (vector.y * vector.y) \
		+ (vector.z * vector.z));
}

double length(double3 vector)
{
	double res;

	res = sqrt(addition_of_squared_elements(vector));
	return (res);
}

double3	unit_direction(double3 vector)
{
	double3	res;

	res = vector / length(vector);
	return (res);
}
