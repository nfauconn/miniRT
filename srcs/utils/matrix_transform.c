/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:50:57 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/13 16:53:36 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_m4x4_f	translation(float x, float y, float z)
{
	t_m4x4_f	res;

	res = identity_matr();
	res[0][3] = x;
	res[1][3] = y;
	res[2][3] = z;
	return (res);
}

t_m4x4_f	scaling(float x, float y, float z)
{
	t_m4x4_f	res;

	res = identity_matr();
	res[0][0] = x;
	res[1][1] = y;
	res[2][2] = z;
	return (res);
}

t_m4x4_f	rotation_x(float angle)
{
	t_m4x4_f	res;

	res = identity_matr();
	res[1][1] = cos(angle);
	res[1][2] = -sin(angle);
	res[2][1] = sin(angle);
	res[2][2] = cos(angle);
	return (res);
}

t_m4x4_f	rotation_y(float angle)
{
	t_m4x4_f	res;

	res = identity_matr();
	res[0][0] = cos(angle);
	res[0][2] = sin(angle);
	res[2][0] = -sin(angle);
	res[2][2] = cos(angle);
	return (res);
}

t_m4x4_f	rotation_z(float angle)
{
	t_m4x4_f	res;

	res = identity_matr();
	res[0][0] = cos(angle);
	res[0][1] = -sin(angle);
	res[1][0] = sin(angle);
	res[1][1] = cos(angle);
	return (res);
}
