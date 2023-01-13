/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_mult.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:09:11 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/13 17:15:24 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

float	dot_product_ma(t_m4x4_f matrix, int line, t_m4x4_f matrix2, int col)
{
	t_float4	tuple1;
	t_float4	tuple2;

	tuple1 = get_vline(line, matrix);
	tuple2 = get_vcol(col, matrix2);
	return (dot_product(tuple1, tuple2));
}

t_m4x4_f	matrix_mult(t_m4x4_f matrix, t_m4x4_f matrix2)
{
	t_m4x4_f	res;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			res[i][j] = dot_product_ma(matrix, i, matrix2, j);
			j++;
		}
		i++;
	}
	return (res);
}

t_float4	get_vline(int i, t_m4x4_f matrix)
{
	t_float4	res;

	res.x = matrix[i][0];
	res.y = matrix[i][1];
	res.z = matrix[i][2];
	res.w = matrix[i][3];
	return (res);
}

t_float4	get_vcol(int i, t_m4x4_f matrix2)
{
	t_float4	res;

	res.x = matrix2[0][i];
	res.y = matrix2[1][i];
	res.z = matrix2[2][i];
	res.w = matrix2[3][i];
	return (res);
}
