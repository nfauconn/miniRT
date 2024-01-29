/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:58:53 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/13 17:03:37 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_m4x4_f	inverse(t_m4x4_f matr)
{
	t_m4x4_f	res;
	float		deter;

	res = cofactor_matrix(matr);
	res = transpose(res);
	deter = determinant_4xf(matr);
	res = divide_matr_by_scalar(res, deter);
	return (res);
}

t_m4x4_f	cofactor_matrix(t_m4x4_f matr)
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
			res[i][j] = cofactor4x(matr, i, j);
			j++;
		}
		i++;
	}
	return (res);
}

float	cofactor4x(t_m4x4_f matrix, int line, int col)
{
	t_m3x3_f	sub;
	float		res;

	sub = submatrix4_to_3(matrix, line, col);
	res = determinant3x3(sub);
	if ((line + col) % 2 == 1)
		res *= -1;
	return (res);
}

float	cofactor(t_m3x3_f matrix, int line, int col)
{
	t_float4	sub;
	float		res;

	sub = submatrix3_to_2(matrix, line, col);
	res = determinant2x2(sub);
	if (line + col % 2 == 1)
		res *= -1;
	return (res);
}

t_m4x4_f	divide_matr_by_scalar(t_m4x4_f res, float deter)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			res[i][j] = res[i][j] / deter;
			j++;
		}
		i++;
	}
	return (res);
}
