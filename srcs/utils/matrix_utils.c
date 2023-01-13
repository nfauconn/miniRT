/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:21:09 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/13 17:14:25 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_float4	matrix_tuple_mult(t_m4x4_f matrix, t_float4 tup)
{
	t_float4	res;
	t_float4	line;
	int			i;

	i = 0;
	while (i < 16)
	{
		line = get_vline(i / 4, matrix);
		res[i / 4] = dot_product(line, tup);
		i += 4;
	}
	return (res);
}

t_m4x4_f	transpose(t_m4x4_f matrix)
{
	t_m4x4_f	res;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			res[i][j] = matrix[j][i];
			j++;
		}
		i++;
	}
	return (res);
}

float	determinant2x2(t_float4 matrix)
{
	float	res;

	res = matrix.x * matrix.w - matrix.y * matrix.z;
	return (res);
}

float	determinant3x3(t_m3x3_f matrix)
{
	float	res;

	res = matrix[0][0] * cofactor(matrix, 0, 0);
	res += matrix[0][1] * cofactor(matrix, 0, 1);
	res += matrix[0][2] * cofactor(matrix, 0, 2);
	return (res);
}

float	determinant_4xf(t_m4x4_f matrix)
{
	return (matrix[0][0] * cofactor4x(matrix, 0, 0)
		+ matrix[0][1] * cofactor4x(matrix, 0, 1)
		+ matrix[0][2] * cofactor4x(matrix, 0, 2)
		+ matrix[0][3] * cofactor4x(matrix, 0, 3));
}
