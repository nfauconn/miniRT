/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_submatrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:13:58 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/13 17:14:14 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

static t_float4	add_f_to_tuple(int i, float val, t_float4 res)
{
	if (i == 0)
		res.x = val;
	if (i == 1)
		res.y = val;
	if (i == 2)
		res.z = val;
	if (i == 3)
		res.w = val;
	return (res);
}

//matr[0][0] to matr[3][3]
t_float4	submatrix3_to_2(t_m3x3_f matr, int line, int col)
{
	t_float4	res;
	int			i;
	int			j;
	int			k;

	i = 0;
	k = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (i != line && j != col)
				res = add_f_to_tuple(k++, matr[i][j], res);
			j++;
		}
		i++;
	}
	return (res);
}

static t_m3x3_f	add_f_to_matrice_3f(int i, float val, t_m3x3_f res)
{
	res[i / 3][i % 3] = val;
	return (res);
}

t_m3x3_f	submatrix4_to_3(t_m4x4_f matr, int line, int col)
{
	t_m3x3_f	res;
	int			i;
	int			j;
	int			k;

	i = 0;
	k = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i != line && j != col)
				res = add_f_to_matrice_3f(k++, matr[i][j], res);
			j++;
		}
		i++;
	}
	return (res);
}
