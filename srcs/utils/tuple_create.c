/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:19:29 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/13 16:19:56 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"

t_float4	create_point(float x, float y, float z)
{
	t_float4	point;

	point.x = x;
	point.y = y;
	point.z = z;
	point.w = 1.0;
	return (point);
}

t_float4	create_vector(float x, float y, float z)
{
	t_float4	point;

	point.x = x;
	point.y = y;
	point.z = z;
	point.w = 0.0;
	return (point);
}
