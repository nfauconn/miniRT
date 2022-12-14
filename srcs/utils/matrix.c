/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:21:09 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/14 18:40:14 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_m4x4_f	matrix_4xf_create(float *f)
{
	t_m4x4_f matrix;
	int	j;
	int	k;
	int	i;

	i = 0;
	j = 0;
	while (j < 4)
	{
		k = 0;
		while (k < 4)
		{
			matrix[j][k] = f[i++];
			k++;
		}
		j++;
	}
	return (matrix);
}

t_m3x3_f	matrix_3xf_create(float *f)
{
	t_m3x3_f matrix;
	int	j;
	int	k;
	int	i;

	i = 0;
	j = 0;
	while (j < 3)
	{
		k = 0;
		while (k < 3)
		{
			matrix[j][k] = f[i++];
			k++;
		}
		j++;
	}
	return (matrix);
}

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
	return(res);
}

//matr[0][0] to matr[3][3]
t_float4	submatrix3_to_2(t_m3x3_f matr, int line, int col)
{
	t_float4	res;
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (i < 3)
	{
		j = 0;
		while (j< 3)
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
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while(i < 4)
	{
		j = 0;
		while (j < 4)
		{
			// printf ("%f\n", tab[j]);
			if (i != line && j != col)
			{
				res = add_f_to_matrice_3f(k++, matr[i][j], res);
			}
			j++;
		}
		i++;
	}
	// printf_3fmatr(res);
	return (res);
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
					return(0);
			k++;
		}
		j++;
	}
	return (1);
}

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
	int	i;
	int	j;

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

t_float4	matrix_tuple_mult(t_m4x4_f matrix, t_float4 tup)
{
	t_float4	res;
	t_float4	line;
	int	i;

	i = 0;
	while (i < 16)
	{
		line = get_vline(i / 4, matrix);
		res[i / 4] = dot_product(line, tup);
		i += 4;
	}
	return (res);
}

t_m4x4_f	divide_matr_by_scalar(t_m4x4_f res, float deter)
{
	int	i;
	int	j;

	i = 0;
	while(i < 4)
	{
		j = 0;
		while (j < 4)
		{
			// printf ("line %d, col %d, val was = %f ", i, j, res[i][j]);
			res[i][j] = res[i][j] / deter;
			// printf ("val is = %f\n", res[i][j]);
			j++;
		}
		i++;
	}
	return (res);
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
t_m4x4_f	transpose(t_m4x4_f matrix)
{
	t_m4x4_f	res;
	int	i;
	int	j;

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

//0 <= j <= 8
//0 <= line <= 2
int	isnotinline(int	j, int line)
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
int	isnotincol(int	j, int col)
{
	if (j % 3  == col)
		return (0);
	return (1);
}

//0 <= j <= 15
//0 <= line <= 3
int	isnotinline_4x4(int	j, int line)
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

int	isnotincol_4x4(int	j, int col)
{
	if (j % 4  == col)
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

	// printf_3fmatr(matrixaim);
	// printf_3fmatr(res);
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (matrixaim[i][j] != res[i][j])
			{
				// printf ("fail at line %d, col %d, 1 = %f, 2 = %f\n", i, j, matrixaim[i][j], res[i][j]);
				return(0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

float	minor_of_3x3(t_m3x3_f matrix, int line, int col)
{
	t_float4	sub;

	sub = submatrix3_to_2(matrix, line, col);
	return (determinant2x2(sub));
}

float	cofactor(t_m3x3_f matrix, int line, int col)
{
	t_float4	sub;
	float	res;

	sub = submatrix3_to_2(matrix, line, col);
	res = determinant2x2(sub);
	if (line + col % 2 == 1)
		res *= -1;
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

float	cofactor4x(t_m4x4_f matrix, int line, int col)
{
	t_m3x3_f	sub;
	float	res;

	sub = submatrix4_to_3(matrix, line, col);
	// printf_3fmatr(sub);
	res = determinant3x3(sub);
	if ((line + col) % 2 == 1)
		res *= -1;
	return (res);
}

float	determinant_4xf(t_m4x4_f matrix)
{
	return (matrix[0][0] * cofactor4x(matrix, 0, 0)
		+ matrix[0][1] * cofactor4x(matrix, 0, 1)
		+ matrix[0][2] * cofactor4x(matrix, 0, 2)
		+ matrix[0][3] * cofactor4x(matrix, 0, 3));
}

bool	is_matrice_invertible(t_m4x4_f matrix)
{
	float	deter;

	deter = determinant_4xf(matrix);
	if (deter == 0)
		return (0);
	return (1);
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
t_m4x4_f	inverse(t_m4x4_f matr)
{
	t_m4x4_f	res;
	float		deter;

	res = cofactor_matrix(matr);
	// printf_4fmatr(res);
	res = transpose(res);
	// printf_4fmatr(res);
	deter = determinant_4xf(matr);
	// printf ("deter = %f\n", deter);
	res = divide_matr_by_scalar(res, deter);
	return (res);
}

t_m4x4_f	identity_matr(void)
{
	float tabf[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	t_m4x4_f matrix = matrix_4xf_create(tabf);
	return (matrix);
}

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

t_m4x4_f	chained_transfo(t_m4x4_f one, t_m4x4_f two, t_m4x4_f three)
{
	t_m4x4_f	res;

	res = matrix_mult(three, two);
	res = matrix_mult(res, one);
	return (res);
}
