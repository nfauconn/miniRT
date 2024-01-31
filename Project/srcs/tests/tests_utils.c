/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:55:57 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/13 16:53:47 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "criterion_utils.h"

void	point_light(t_elem *light, t_point pos, t_rgb color)
{
	light->w_pos = pos;
	light->color = color;
}
/* verifie que les deux tuples en arguments on les memes valeurs
a une precision de 0.00001 */
bool	same_tuple(t_float4 tup1, t_float4 tup2)
{
	if (fabs(tup1.x - tup2.x) > EPSILON || fabs(tup1.y - tup2.y) > EPSILON
		|| fabs(tup1.z - tup2.z) > EPSILON || fabs(tup1.w - tup2.w) > EPSILON)
		return (0);
	return (1);
}

/* verifie si un tuple de bolleen a un element valant 0 --> fail */
bool	tuple_bool(t_int4 tuple)
{
	if (tuple.x == 0 || tuple.y == 0 || tuple.z == 0 || tuple.w == 0)
		return (0);
	return (1);
}

/* verifie que les deux arguments float ont la meme valeur,
avec 0.00001 de precision(EPSILON)*/
bool	same_float(float f1, float f2)
{
	if (fabs(f1 - f2) > EPSILON)
		return (0);
	return (1);
}

t_m4x4_f	shearing(float	*tab)
{
	t_m4x4_f	res;

	res = identity_matr();
	res[0][1] = tab[0];
	res[0][2] = tab[1];
	res[1][0] = tab[2];
	res[1][2] = tab[3];
	res[2][0] = tab[4];
	res[2][1] = tab[5];
	return (res);
}

bool	is_matrice_invertible(t_m4x4_f matrix)
{
	float	deter;

	deter = determinant_4xf(matrix);
	if (deter == 0)
		return (0);
	return (1);
}

float	minor_of_3x3(t_m3x3_f matrix, int line, int col)
{
	t_float4	sub;

	sub = submatrix3_to_2(matrix, line, col);
	return (determinant2x2(sub));
}

//0 <= j <= 8
//0 <= line <= 2
int	isnotinline(int j, int line)
{
	if (j >= 0 && j <= 2 && line == 0)
		return (0);
	if (j >= 3 && j <= 5 && line == 1)
		return (0);
	if (j >= 6 && j <= 8 && line == 2)
		return (0);
	return (1);
}

//0 3 6  (col 0)
//1 4 7  (col 1)
//2 5 8  (col 2)
int	isnotincol(int j, int col)
{
	if (j % 3 == col)
		return (0);
	return (1);
}

//0 <= j <= 15
//0 <= line <= 3
int	isnotinline_4x4(int j, int line)
{
	if (j >= 0 && j <= 3 && line == 0)
		return (0);
	if (j >= 4 && j <= 7 && line == 1)
		return (0);
	if (j >= 8 && j <= 11 && line == 2)
		return (0);
	if (j >= 12 && j <= 15 && line == 3)
		return (0);
	return (1);
}

int	isnotincol_4x4(int j, int col)
{
	if (j % 4 == col)
		return (0);
	return (1);
}

void	printf_3fmatr(t_m3x3_f	matrixaim)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			printf ("line %d, col %d, val = %f\n", i, j, matrixaim[i][j]);
			j++;
		}
		i++;
	}
}

bool	same_matrix_3x3(t_m3x3_f matrixaim, t_m3x3_f res)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (matrixaim[i][j] != res[i][j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

bool	same_matrix(t_m4x4_f matrix1, t_m4x4_f matrix2)
{
	int	j;
	int	k;

	j = 0;
	while (j < 4)
	{
		k = 0;
		while (k < 4)
		{
			if (matrix1[j][k] >= matrix2[j][k] + EPSILON
				|| matrix1[j][k] <= matrix2[j][k] - EPSILON)
				return (0);
			k++;
		}
		j++;
	}
	return (1);
}

void	printf_4fmatr(t_m4x4_f	matrixaim)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf ("line %d, col %d, val = %f\n", i, j, matrixaim[i][j]);
			j++;
		}
		i++;
	}
}

t_m4x4_f	chained_transfo(t_m4x4_f one, t_m4x4_f two, t_m4x4_f three)
{
	t_m4x4_f	res;

	res = matrix_mult(three, two);
	res = matrix_mult(res, one);
	return (res);
}
