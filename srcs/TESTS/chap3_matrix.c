/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chap3_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:12:44 by rokerjea          #+#    #+#             */
/*   Updated: 2022/12/07 17:18:02 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/mnt/nfs/homes/nfauconn/Criterion/include/criterion/criterion.h"
//#include "/mnt/nfs/homes/rokerjea/sgoinfre/Criterion/include/criterion/criterion.h"
#include "matrix.h"
#include "tuple.h"
# include <math.h>
# include <stdio.h>
# include <signal.h>
# include <errno.h>

// typedef float	float16	__attribute__((ext_vector_type(16)));
typedef float t_m4x4_f  __attribute__((matrix_type(4, 4)));
typedef float t_m3x3_f __attribute__((matrix_type(4, 4)));
typedef int t_m4x4_i __attribute__((matrix_type(4, 4)));
// typedef int	int16	__attribute__((ext_vector_type(16)));
// typedef float	t_matrix4	__attribute__((ext_vector_type(16)));
// typedef float	t_matrix3	__attribute__((ext_vector_type(16)));
// typedef int	int9	__attribute__((ext_vector_type(9)));
typedef float float4 __attribute__((ext_vector_type(4)));
typedef int	int4 __attribute__((ext_vector_type(4)));

// int	any_matrix(t_m4x4_i bool_matrix)
// {
	
// 	int	j;
// 	int	k;
	
// 	i = 0;
// 	j = 0;
// 	while (j < 4)
// 	{
// 		k = 0;
// 		while (k < 4)
// 		{
// 			if (bool_matrix[j][k] != 0)
// 				return(0);
// 		}
// 		j++;		
// 	}
// 	return (1);
// }

// t_m4x4_f	matrix_4xf_create(float *f)
// {
// 	t_m4x4_f matrix;
// 	int	j;
// 	int	k;
// 	int	i;
	
// 	i = 0;
// 	j = 0;
// 	while (j < 4)
// 	{
// 		k = 0;
// 		while (k < 4)
// 		{
// 			matrix[j][k] = f[i++];
// 			k++;
// 		}
// 		j++;		
// 	}
// 	return (matrix);	
// }

Test(matrix, matrix_create)
{
	t_m4x4_f matrix;
	float tabf[16] = {1, 2, 3, 4, 5.5, 6.5, 7.5, 8.5, 9, 10, 11, 12, 13.5, 14.5, 15.5, 16.5};
	matrix = matrix_4xf_create(tabf);
	// printf ("%f\n", matrix[0][0]);
	cr_expect(same_float(matrix[0][0], 1));
	cr_expect(same_float(matrix[0][3], 4));
	cr_expect(same_float(matrix[1][0], 5.5) == 1);
	cr_expect(same_float(matrix[1][2], 7.5) == 1);
	cr_expect(same_float(matrix[2][2], 11) == 1);
	cr_expect(same_float(matrix[3][0], 13.5) == 1);
	cr_expect(same_float(matrix[3][2], 15.5) == 1);
	cr_expect(same_float(matrix[3][3], 16.5) == 1);
}

// bool	same_matrix(t_m4x4_f matrix1, t_m4x4_f matrix2)
// {
// 	int	j;
// 	int	k;
// 	float	epsilon;

// 	epsilon = 0.00001;
// 	j = 0;
// 	while (j < 4)
// 	{
// 		k = 0;
// 		while (k < 4)
// 		{
// 			if (matrix1[j][k] >= matrix2[j][k] + epsilon
// 				|| matrix1[j][k] <= matrix2[j][k] - epsilon)
// 				{
// 					// printf ("%f != %f\n", matrix1[j][k], matrix2[j][k]);
// 					return(0);
// 				}
// 			k++;
// 		}
// 		j++;
// 	}
// 	return (1);
// }

Test(matrix, matrix_compare)
{
	float tabf[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
	float tabf2[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
	t_m4x4_f matrix = matrix_4xf_create(tabf);
	t_m4x4_f matrix2 = matrix_4xf_create(tabf2);
	cr_expect(same_matrix(matrix, matrix2) == 1);
	float tabf3[16] = {1.5, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 15};
	matrix2 = matrix_4xf_create(tabf3);
	cr_expect(same_matrix(matrix, matrix2) == 0);
}

// // float4	get_line(float16 matrix, int line)
// // {
// // 	float4	res;
	
// // 	if (line / 4 == 0)
// // 		res = matrix.s0123;
// // }


// float4	get_vline(int i, t_m4x4_f matrix)
// {
// 	float4	res;

// 	res.x = matrix[i][0];
// 	res.y = matrix[i][1];
// 	res.z = matrix[i][2];
// 	res.w = matrix[i][3];
// 	return (res);
// }

// float4	get_vcol(int i, t_m4x4_f matrix2)
// {
// 	float4	res;

// 	res.x = matrix2[0][i];
// 	res.y = matrix2[1][i];
// 	res.z = matrix2[2][i];
// 	res.w = matrix2[3][i];
// 	return (res);
// }

// float	dot_product_ma(t_m4x4_f matrix, int line, t_m4x4_f matrix2, int col)
// {
// 	float4	tuple1;
// 	float4	tuple2;

// 	tuple1 = get_vline(line, matrix);
// 	tuple2 = get_vcol(col, matrix2);
// 	return (dot_product(tuple1, tuple2));
// }

// t_m4x4_f	matrix_mult(t_m4x4_f matrix, t_m4x4_f matrix2)
// {
// 	t_m4x4_f	res;
// 	int	i;
// 	int	j;
	
// 	i = 0;
// 	j = 0;
// 	while (i < 4)
// 	{
// 		j = 0;
// 		while (j < 4)
// 		{
// 			res[i][j] = dot_product_ma(matrix, i, matrix2, j);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (res);
// }

Test(matrix, matrix_mult)
{	float tabf[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
	float tabf2[16] = {-2, 1, 2, 3, 3, 2, 1, -1, 4, 3, 6, 5, 1, 2, 7, 8};
	t_m4x4_f matrix = matrix_4xf_create(tabf);
	t_m4x4_f matrix2 = matrix_4xf_create(tabf2);
	float	test;
	test = dot_product_ma(matrix, 2, matrix2, 3);
	cr_expect(same_float(test, 102) == 1, "internal step of matrix multiplication");
	t_m4x4_f matrix3 = matrix_mult(matrix, matrix2);
	float tabf3[16] = {20, 22, 50, 48, 44, 54, 114, 108, 40, 58, 110, 102, 16, 26, 46, 42};
	t_m4x4_f matrix4 = matrix_4xf_create(tabf3);
	cr_expect(same_matrix(matrix3, matrix4) == 1, "multiplication of full matrix");
}

// float4	matrix_tuple_mult(t_m4x4_f matrix, float4 tup)
// {
// 	float4	res;
// 	float4	line;
// 	int	i;

// 	i = 0;
// 	while (i < 16)
// 	{
// 		line = get_vline(i / 4, matrix);
// 		res[i / 4] = dot_product(line, tup);
// 		i += 4;
// 	}
// 	return (res);
// }

Test(matrix, matrix_tuple_mult)
{	float tabf[16] = {1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1};
	t_m4x4_f matrix = matrix_4xf_create(tabf);
	float4	tup = (float4){1, 2, 3, 1};
	float4	res = (float4){18, 24, 33, 1};
	float4	test = matrix_tuple_mult(matrix, tup);
	// printf("%f %f %f %f\n", test.x, test.y, test.z, test.w);
	// printf("%f %f %f %f\n", res.x, res.y, res.z, res.w);
	cr_expect(same_tuple(test, res) == 1, "multiplication of matrix by tuple");
}

Test(matrix, identity_matrix)
{
	float tabf[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
	t_m4x4_f matrix = matrix_4xf_create(tabf);
	float tabf2[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	t_m4x4_f matrix2 = matrix_4xf_create(tabf2);
	t_m4x4_f	test;
	test = matrix_mult(matrix, matrix2);
	cr_expect(same_matrix(test, matrix) == 1, "identity mtrx multi");
	float4	res = (float4){18, 24, 33, 1};
	float4	test2 = matrix_tuple_mult(matrix2, res);
	cr_expect(same_tuple(test2, res) == 1, "multiplication of identity mtrx by tuple");
}

// t_m4x4_f	transpose(t_m4x4_f matrix)
// {
// 	t_m4x4_f	res;
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		j = 0;
// 		while (j < 4)
// 		{
// 			res[i][j] = matrix[j][i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (res);
// }

Test(matrix, transposing_matrix)
{
	float tabf[16] = {0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8};
	t_m4x4_f matrix = matrix_4xf_create(tabf);
	t_m4x4_f matrixres;
	float tabf2[16] = {0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8};
	t_m4x4_f matrixaim = matrix_4xf_create(tabf2);
	matrixres = transpose(matrix);
	cr_expect(same_matrix(matrixres, matrixaim) == 1);
	float tabf3[16] = {0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 5, 8};
	t_m4x4_f matrixaim2 = matrix_4xf_create(tabf3);
	cr_expect(same_matrix(matrixres, matrixaim2) == 0);
	float tabf4[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	t_m4x4_f matrix2 = matrix_4xf_create(tabf4);
	t_m4x4_f matrixres2 = transpose(matrix2);
	cr_expect(same_matrix(matrixres2, matrix2) == 1);
}

// float	determinant2x2(float4 matrix)
// {
// 	float	res;
	
// 	res = matrix.x * matrix.w - matrix.y * matrix.z;
// 	return (res);
// }

Test(matrix, determinant2x2)
{
	float4	matrix2x2 = (float4){1, 5, -3, 2};
	float	aim = 17;
	float	res = determinant2x2(matrix2x2);
	cr_expect(same_float(aim, res) == 1);
}

// bool	same_tuple(float4 tup1, float4 tup2)
// {
// 	float	epsilon;

// 	epsilon = 0.00001;
// 	if (fabs(tup1.x - tup2.x) > epsilon || fabs(tup1.y - tup2.y) > epsilon
// 		|| fabs(tup1.z - tup2.z) > epsilon || fabs(tup1.w - tup2.w) > epsilon)
// 		return (0);
// 	return (1);
// }

//0 <= j <= 8
//0 <= line <= 2
// int	isnotinline(int	j, int line)
// {
// 	if (j >= 0 && j <= 2 && line == 0)
// 		return (0);
// 	if (j >= 3 && j <= 5 && line == 1)
// 		return (0);
// 	if (j >= 6 && j <= 8 && line == 2)
// 		return (0);
// 	return (1);
// }

// //0 3 6  (col 0)
// //1 4 7  (col 1)
// //2 5 8  (col 2)
// int	isnotincol(int	j, int col)
// {
// 	if (j % 3  == col)
// 		return (0);
// 	return (1);
// }


// float4	add_f_to_tuple(int i, float val, float4 res)
// {
// 	if (i == 0)
// 		res.x = val;
// 	if (i == 1)
// 		res.y = val;
// 	if (i == 2)
// 		res.z = val;
// 	if (i == 3)
// 		res.w = val;
// 	return(res);
// }

//matr[0][0] to matr[3][3]
// float4	submatrix3_to_2(t_m3x3_f matr, int line, int col)
// {
// 	float4	res;
// 	int	i;
// 	int	j;
// 	int	k;
	
// 	i = 0;
// 	k = 0;
// 	while (i < 3)
// 	{
// 		j = 0;
// 		while (j< 3)
// 		{
// 			if (i != line && j != col)
// 				res = add_f_to_tuple(k++, matr[i][j], res);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (res);
// }

//0 <= j <= 15
//0 <= line <= 3
// int	isnotinline_4x4(int	j, int line)
// {
// 	if (j >= 0 && j <= 3 && line == 0)
// 		return (0);
// 	if (j >= 4 && j <= 7 && line == 1)
// 		return (0);
// 	if (j >= 8 && j <= 11 && line == 2)
// 		return (0);
// 	if (j >= 12 && j <= 15 && line == 3)
// 		return (0);
// 	return (1);
// }

// int	isnotincol_4x4(int	j, int col)
// {
// 	if (j % 4  == col)
// 		return (0);
// 	return (1);
// }

// t_matrix3	convert_tab_to_matr_3x3(float	tab[9])
// {
// 	t_matrix3	res;
// 	// float	tabres[9] = {res.s0, res.s1, res.s2, res.s3,
// 	// 	res.s4, res.s5, res.s6, res.s7, res.s8};
// 	int	i;

// 	i = 0;
// 	while (i < 9)
// 	{
// 		res[i] = tab[i];
// 		// printf ("%f, ", tabres[i]);
// 		i++;
// 	}
// 	// printf("\n");
// 	return (res);
// }
// t_m3x3_f	add_f_to_matrice_3f(int i, float val, t_m3x3_f res)
// {
// 	res[i / 3][i % 3] = val;
// 	return (res);
// }
// void	printf_3fmatr(t_m3x3_f	matrixaim)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < 3)
// 	{
// 		j = 0;
// 		while (j < 3)
// 		{
// 			printf ("line %d, col %d, val = %f\n", i, j, matrixaim[i][j]);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// t_m3x3_f	submatrix4_to_3(t_m4x4_f matr, int line, int col)
// {
// 	t_m3x3_f	res;
// 	int	i;
// 	int	j;
// 	int	k;
	
// 	i = 0;
// 	k = 0;
// 	while(i < 4)
// 	{
// 		j = 0;
// 		while (j < 4)
// 		{
// 			// printf ("%f\n", tab[j]);
// 			if (i != line && j != col)
// 			{
// 				res = add_f_to_matrice_3f(k++, matr[i][j], res);
// 			}
// 			j++;
// 		}		
// 		i++;
// 	}
// 	// printf_3fmatr(res);
// 	return (res);
// }

// t_m3x3_f	matrix_3xf_create(float *f)
// {
// 	t_m3x3_f matrix;
// 	int	j;
// 	int	k;
// 	int	i;
	
// 	i = 0;
// 	j = 0;
// 	while (j < 3)
// 	{
// 		k = 0;
// 		while (k < 3)
// 		{
// 			matrix[j][k] = f[i++];
// 			k++;
// 		}
// 		j++;		
// 	}
// 	return (matrix);	
// }

Test(matrix, submatrix)
{
	float tabf[9] = {1, 5, 0, -3, 2, 7, 0, 6, -3};
	t_m3x3_f	matrix = matrix_3xf_create(tabf);
	float4		aim = (float4){-3, 2, 0, 6};
	
	float4		res = submatrix3_to_2(matrix, 0, 2);
	
	cr_expect(same_tuple(aim, res) == 1);
}

// bool	same_matrix_3x3(t_m3x3_f matrixaim, t_m3x3_f res)
// {

// 	// printf_3fmatr(matrixaim);
// 	// printf_3fmatr(res);
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < 3)
// 	{
// 		j = 0;
// 		while (j < 3)
// 		{
// 			if (matrixaim[i][j] != res[i][j])
// 			{
// 				// printf ("fail at line %d, col %d, 1 = %f, 2 = %f\n", i, j, matrixaim[i][j], res[i][j]);
// 				return(0);
// 			}
// 			j++;
// 		}
// 		i++;		
// 	}
// 	return (1);
// }

// bool	testeurmatr3(t_m3x3_f aim, t_m3x3_f res)
// {
// 	(void)aim;
// 	printf ("TES??? %f\n", res[0][1]);
// 	printf_3fmatr(res);
// 	return (1);
// }

Test(matrix, submatrix2)
{
	float tabf[16] = {-6, 1, 1, 6, -8, 5, 8, 6, -1, 0, 8, 2, -7, 1, -1, 1};
	t_m4x4_f matrix = matrix_4xf_create(tabf);
	float tabf2[9] = {-6, 1, 6, -8, 8, 6, -7, -1, 1};
	t_m3x3_f matrixaim = matrix_3xf_create(tabf2);
	t_m3x3_f	res = submatrix4_to_3(matrix, 2, 1);
	// printf_3fmatr(matrixaim);
	// printf_3fmatr(res);
	// printf ("TES??? %f\n", res[0][1]);
	cr_expect(same_matrix_3x3(matrixaim, res) == 1);
}

// float	minor_of_3x3(t_m3x3_f matrix, int line, int col)
// {
// 	float4	sub;

// 	sub = submatrix3_to_2(matrix, line, col);
// 	return (determinant2x2(sub));
// }

Test(matrix, minor)
{
	float tabf2[9] = {3, 5, 0, 2, -1, -7, 6, -1, 5};
	t_m3x3_f	matrix  = matrix_3xf_create(tabf2);
	float4		sub = submatrix3_to_2(matrix, 1, 0);
	float		determinant = determinant2x2(sub);
	cr_expect(same_float(determinant, 25) == 1);
	float		determinant2 = minor_of_3x3(matrix, 1, 0);
	cr_expect(same_float(determinant2, 25) == 1);
	cr_expect(same_float(determinant2, 24) == 0);	
}

// float	cofactor(t_m3x3_f matrix, int line, int col)
// {
// 	float4	sub;
// 	float	res;

// 	sub = submatrix3_to_2(matrix, line, col);
// 	res = determinant2x2(sub);
// 	if (line + col % 2 == 1)
// 		res *= -1;
// 	return (res);
// }

Test(matrix, cofactor)
{
	float tabf2[9] = {3, 5, 0, 2, -1, -7, 6, -1, 5};
	t_m3x3_f	matrix  = matrix_3xf_create(tabf2);
	float	minor = -12;
	float	cofactortest = cofactor(matrix, 0, 0);
	cr_expect(same_float(minor, cofactortest) == 1);
	cofactortest = cofactor(matrix, 1, 0);
	cr_expect(same_float(-25, cofactortest) == 1);
}

// float	determinant3x3(t_m3x3_f matrix)
// {
// 	float	res;
	
// 	res = matrix[0][0] * cofactor(matrix, 0, 0);
// 	res += matrix[0][1] * cofactor(matrix, 0, 1);
// 	res += matrix[0][2] * cofactor(matrix, 0, 2);
// 	return (res);
// }

Test(matrix, determinant3x3)
{
	float tabf2[9] = {1, 2, 6, -5, 8, -4, 2, 6, 4};
	t_m3x3_f	matrix  = matrix_3xf_create(tabf2);
	float	cofactor1 = cofactor(matrix, 0, 0);
	float	cofactor2 = cofactor(matrix, 0, 1);
	float	cofactor3 = cofactor(matrix, 0, 2);
	cr_expect(same_float(56, cofactor1) == 1);
	cr_expect(same_float(12, cofactor2) == 1);
	cr_expect(same_float(-46, cofactor3) == 1);
	float	determinanttest = determinant3x3(matrix);
	cr_expect (same_float(determinanttest, -196) == 1);
}

// float	cofactor4x(t_m4x4_f matrix, int line, int col)
// {
// 	t_m3x3_f	sub;
// 	float	res;

// 	sub = submatrix4_to_3(matrix, line, col);
// 	// printf_3fmatr(sub);
// 	res = determinant3x3(sub);
// 	if ((line + col) % 2 == 1)
// 		res *= -1;
// 	return (res);
// }

// float	determinant_4xf(t_m4x4_f matrix)
// {
// 	return (matrix[0][0] * cofactor4x(matrix, 0, 0)
// 		+ matrix[0][1] * cofactor4x(matrix, 0, 1)
// 		+ matrix[0][2] * cofactor4x(matrix, 0, 2)
// 		+ matrix[0][3] * cofactor4x(matrix, 0, 3));
// }

// bool	is_matrice_invertible(t_m4x4_f matrix)
// {
// 	float	deter;
	
// 	deter = determinant_4xf(matrix);
// 	if (deter == 0)
// 		return (0);
// 	return (1);
// }

Test(matrix, determinant4x4)
{
	float tabf[16] = {-2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9};
	t_m4x4_f matrix = matrix_4xf_create(tabf);
	float	cofactor1 = cofactor4x(matrix, 0, 0);
	float	cofactor2 = cofactor4x(matrix, 0, 1);
	float	cofactor3 = cofactor4x(matrix, 0, 2);
	float	cofactor4 = cofactor4x(matrix, 0, 3);
	cr_expect(same_float(690, cofactor1) == 1);
	cr_expect(same_float(447, cofactor2) == 1);
	cr_expect(same_float(210, cofactor3) == 1);
	cr_expect(same_float(51, cofactor4) == 1);
	float	deteeminant = determinant_4xf(matrix);
	cr_expect(same_float(deteeminant, -4071) == 1);
}

Test(matrix, is_invertible)
{
	float tabf[16] = {6, 4, 4, 4, 5, 5, 7, 6, 4, -9, 3, -7, 9, 1, 7, -6};
	t_m4x4_f matrix = matrix_4xf_create(tabf);
	cr_expect(is_matrice_invertible(matrix) == 1);
	float tabf2[16] = {-4, 2, -2, -3, 9, 6, 2, 6, 0, -5, 1, -5, 0, 0, 0, 0};
	t_m4x4_f matrix2 = matrix_4xf_create(tabf2);
	cr_expect(is_matrice_invertible(matrix2) == 0);
}

// t_m4x4_f	cofactor_matrix(t_m4x4_f matr)
// {
// 	t_m4x4_f	res;
// 	int			i;
// 	int			j;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		j = 0;
// 		while (j < 4)
// 		{
// 			res[i][j] = cofactor4x(matr, i, j);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (res);
// }

// t_m4x4_f	divide_matr_by_scalar(t_m4x4_f res, float deter)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while(i < 4)
// 	{
// 		j = 0;
// 		while (j < 4)
// 		{
// 			// printf ("line %d, col %d, val was = %f ", i, j, res[i][j]);
// 			res[i][j] = res[i][j] / deter;
// 			// printf ("val is = %f\n", res[i][j]);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (res);
// }

// void	printf_4fmatr(t_m4x4_f	matrixaim)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		j = 0;
// 		while (j < 4)
// 		{
// 			printf ("line %d, col %d, val = %f\n", i, j, matrixaim[i][j]);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// t_m4x4_f	inverse(t_m4x4_f matr)
// {
// 	t_m4x4_f	res;
// 	float		deter;

// 	res = cofactor_matrix(matr);
// 	// printf_4fmatr(res);
// 	res = transpose(res);
// 	// printf_4fmatr(res);
// 	deter = determinant_4xf(matr);
// 	// printf ("deter = %f\n", deter);
// 	res = divide_matr_by_scalar(res, deter);
// 	return (res);
// }

Test(matrix, inverse)
{
	float tabf[16] = {-5, 2, 6, -8, 1, -5, 1, 8, 7, 7, -6, -7, 1, -3, 7, 4};
	t_m4x4_f matrix = matrix_4xf_create(tabf);
	float	cofactor4 = cofactor4x(matrix, 3, 0);
	// printf ("%f\n", cofactor4);
	cr_expect(same_float(-24, cofactor4) == 1);
	float tabf2[16] = {0.21805, 0.45113, 0.24060, -0.04511, -0.80827, -1.45677, -0.44361, 0.52068, -0.07895, -0.22368, -0.05263, 0.19737, -0.52256, -0.81391, -0.30075, 0.30639};
	t_m4x4_f matrix2 = matrix_4xf_create(tabf2);
	t_m4x4_f res = inverse(matrix);
	// printf_4fmatr(res);
	cr_expect(same_matrix(res, matrix2) == 1);
}

Test(matrix, inversion2)
{
	float tabf[16] = {8, -5, 9, 2, 7, 5, 6, 1, -6, 0, 9, 6, -3, 0, -9, -4};
	t_m4x4_f matrix = matrix_4xf_create(tabf);
	float tabf2[16] = {-0.15385, -0.15385, -0.28205, -0.53846, -0.07692, 0.12308, 0.02564, 0.03077, 0.35897, 0.35897, 0.43590, 0.92308, -0.69231, -0.69231, -0.76923, -1.92308};
	t_m4x4_f matrix2 = matrix_4xf_create(tabf2);
	cr_expect(same_matrix(matrix2, inverse(matrix)));
	float tabf3[16] = {9, 3, 0, 9, -5, -2, -6, -3, -4, 9, 6, 4, -7, 6, 6, 2};
	t_m4x4_f matrix3 = matrix_4xf_create(tabf3);
	float tabf4[16] = {-0.04074, -0.07778, 0.14444, -0.22222, -0.07778, 0.03333, 0.36667, -0.33333, -0.02901, -0.14630, -0.10926, 0.12963, 0.17778, 0.06667, -0.26667, 0.33333};
	t_m4x4_f matrix4 = matrix_4xf_create(tabf4);
	cr_expect(same_matrix(matrix4, inverse(matrix3)));
}

Test(matrix, inversion3)
{
	float tabf[16] = {3, -9, 7, 3, 3, -8, 2, -9, -4, 4, 4, 1, -6, 5, -1, 1};
	t_m4x4_f matrix = matrix_4xf_create(tabf);
	float tabf2[16] = {8, 2, 2, 2, 3, -1, 7, 0, 7, 0, 5, 4, 6, -2, 0, 5};
	t_m4x4_f matrix2 = matrix_4xf_create(tabf2);
	t_m4x4_f matrix3 = matrix * matrix2;
	cr_expect(same_matrix(matrix, matrix3 * inverse(matrix2)));
}

// t_m4x4_f	identity_matr(void)
// {
// 	float tabf[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
// 	t_m4x4_f matrix = matrix_4xf_create(tabf);
// 	return (matrix);
// }

// t_m4x4_f	translation(float x, float y, float z)
// {
// 	t_m4x4_f	res;

// 	res = identity_matr();
// 	res[0][3] = x;
// 	res[1][3] = y;
// 	res[2][3] = z;
// 	return (res);
// }

Test(matrix, translation)
{
	t_m4x4_f	matr_transf = translation(5, -3, 2);
	// t_m4x4_f	matr_inv = inverse(matr_transf);
	float4	test = (float4){-3, 4, 5, 1};
	float4	res = matrix_tuple_mult(matr_transf, test);
	float4	point = (float4){2, 1, 7, 1};
	// printf("%f, %f, %f, %f\n", res.x, res.y, res.z, res.w);
	cr_expect(same_tuple(point, res) == 1);
}

Test(matrix, translation2)
{
	t_m4x4_f	matr_transf = translation(5, -3, 2);
	t_m4x4_f	matr_inv = inverse(matr_transf);
	float4	test = (float4){-3, 4, 5, 1};
	float4	res = matrix_tuple_mult(matr_inv, test);
	float4	point = (float4){-8, 7, 3, 1};
	// printf("%f, %f, %f, %f\n", res.x, res.y, res.z, res.w);
	cr_expect(same_tuple(point, res) == 1);
}

Test(matrix, translation3)
{
	t_m4x4_f	matr_transf = translation(5, -3, 2);
	float4	test = (float4){-3, 4, 5, 0};
	float4	res = matrix_tuple_mult(matr_transf, test);
	float4	point = (float4){-3, 4, 5, 0};
	// printf("%f, %f, %f, %f\n", res.x, res.y, res.z, res.w);
	cr_expect(same_tuple(point, res) == 1);
}

// t_m4x4_f	scaling(float x, float y, float z)
// {
// 	t_m4x4_f	res;

// 	res = identity_matr();
// 	res[0][0] = x;
// 	res[1][1] = y;
// 	res[2][2] = z;
// 	return (res);
// }

Test(matrix, scaling1)
{
	t_m4x4_f	matr_scale = scaling(2, 3, 4);
	float4	mult = (float4){-4, 6, 8, 0};
	float4	res = matrix_tuple_mult(matr_scale, mult);
	float4	aim = (float4){-8, 18, 32, 0};
	cr_expect(same_tuple(aim, res) == 1);
}

Test(matrix, scaling2)
{
	t_m4x4_f	matr_scale = scaling(2, 3, 4);
	float4	mult = (float4){-4, 6, 8, 1};
	float4	res = matrix_tuple_mult(matr_scale, mult);
	float4	aim = (float4){-8, 18, 32, 1};
	cr_expect(same_tuple(aim, res) == 1);
}

Test(matrix, scaling3)
{
	t_m4x4_f	matr_scale = scaling(2, 3, 4);
	t_m4x4_f	matr_inv = inverse(matr_scale);
	float4	mult = (float4){-4, 6, 8, 1};
	float4	res = matrix_tuple_mult(matr_inv, mult);
	float4	aim = (float4){-2, 2, 2, 1};
	cr_expect(same_tuple(aim, res) == 1);
}

Test(matrix, reflection)
{
	t_m4x4_f	matr_scale = scaling(-1, 1, 1);
	float4	mult = (float4){2, 3, 4, 0};
	float4	res = matrix_tuple_mult(matr_scale, mult);
	float4	aim = (float4){-2, 3, 4};
	cr_expect(same_tuple(aim, res) == 1);
}

// t_m4x4_f	rotation_x(float angle)
// {
// 	t_m4x4_f	res;

// 	res = identity_matr();
// 	res[1][1] = cos(angle);
// 	res[1][2] = -sin(angle);
// 	res[2][1] = sin(angle);
// 	res[2][2] = cos(angle);
// 	return (res);
// }

Test(matrix, rotate_x)
{
	float4	p = (float4){0, 1, 0, 0};
	t_m4x4_f	half_quart = rotation_x(M_PI / 4);
	float4	half_quart_res = matrix_tuple_mult(half_quart, p);
	t_m4x4_f	full_quart = rotation_x(M_PI / 2);
	float4	full_quart_res = matrix_tuple_mult(full_quart, p);
	float4	aim_1 = (float4){0, sqrt(2) / 2, sqrt(2) / 2, 0};
	float4	aim_2 = (float4){0, 0, 1, 0};
	cr_expect(same_tuple(half_quart_res, aim_1) == 1);
	cr_expect(same_tuple(full_quart_res, aim_2) == 1);
}

// t_m4x4_f	rotation_y(float angle)
// {
// 	t_m4x4_f	res;

// 	res = identity_matr();
// 	res[0][0] = cos(angle);
// 	res[0][2] = sin(angle);
// 	res[2][0] = -sin(angle);
// 	res[2][2] = cos(angle);
// 	return (res);
// }

Test(matrix, rotate_y)
{
	float4	p = (float4){0, 0, 1, 0};
	t_m4x4_f	half_quart = rotation_y(M_PI / 4);
	float4	half_quart_res = matrix_tuple_mult(half_quart, p);
	t_m4x4_f	full_quart = rotation_y(M_PI / 2);
	float4	full_quart_res = matrix_tuple_mult(full_quart, p);
	float4	aim_1 = (float4){sqrt(2) / 2, 0, sqrt(2) / 2, 0};
	float4	aim_2 = (float4){1, 0, 0, 0};
	cr_expect(same_tuple(half_quart_res, aim_1) == 1);
	cr_expect(same_tuple(full_quart_res, aim_2) == 1);
}

// t_m4x4_f	rotation_z(float angle)
// {
// 	t_m4x4_f	res;

// 	res = identity_matr();
// 	res[0][0] = cos(angle);
// 	res[0][1] = -sin(angle);
// 	res[1][0] = sin(angle);
// 	res[1][1] = cos(angle);
// 	return (res);
// }

Test(matrix, rotation_z)
{
	float4	p = (float4){0, 1, 0, 0};
	t_m4x4_f	half_quart = rotation_z(M_PI / 4);
	float4	half_quart_res = matrix_tuple_mult(half_quart, p);
	t_m4x4_f	full_quart = rotation_z(M_PI / 2);
	float4	full_quart_res = matrix_tuple_mult(full_quart, p);
	float4	aim_1 = (float4){-(sqrt(2) / 2), sqrt(2) / 2, 0, 0};
	float4	aim_2 = (float4){-1, 0, 0, 0};
	cr_expect(same_tuple(half_quart_res, aim_1) == 1);
	cr_expect(same_tuple(full_quart_res, aim_2) == 1);
}

// t_m4x4_f	shearing(float	*tab)
// {
// 	t_m4x4_f	res;

// 	res = identity_matr();
// 	res[0][1] = tab[0];
// 	res[0][2] = tab[1];
// 	res[1][0] = tab[2];
// 	res[1][2] = tab[3];
// 	res[2][0] = tab[4];
// 	res[2][1] = tab[5];
// 	return (res);
// }

Test(matrix, shearing1)
{
	float	tab[6] = {1, 0, 0, 0, 0, 0};
	t_m4x4_f 	transf = shearing(tab);
	float4	p = (float4){2, 3, 4, 0};
	float4	aim = (float4){5, 3, 4, 0};
	p = matrix_tuple_mult(transf, p);
	cr_expect(same_tuple(p, aim) == 1);
}
Test(matrix, shearing2)
{
	float	tab[6] = {0, 1, 0, 0, 0, 0};
	t_m4x4_f 	transf = shearing(tab);
	float4	p = (float4){2, 3, 4, 0};
	float4	aim = (float4){6, 3, 4, 0};
	p = matrix_tuple_mult(transf, p);
	cr_expect(same_tuple(p, aim) == 1);
}
Test(matrix, shearing3)
{
	float	tab[6] = {0, 0, 1, 0, 0, 0};
	t_m4x4_f 	transf = shearing(tab);
	float4	p = (float4){2, 3, 4, 0};
	float4	aim = (float4){2, 5, 4, 0};
	p = matrix_tuple_mult(transf, p);
	cr_expect(same_tuple(p, aim) == 1);
}
Test(matrix, shearing4)
{
	float	tab[6] = {0, 0, 0, 1, 0, 0};
	t_m4x4_f 	transf = shearing(tab);
	float4	p = (float4){2, 3, 4, 0};
	float4	aim = (float4){2, 7, 4, 0};
	p = matrix_tuple_mult(transf, p);
	cr_expect(same_tuple(p, aim) == 1);
}
Test(matrix, shearing5)
{
	float	tab[6] = {0, 0, 0, 0, 1, 0};
	t_m4x4_f 	transf = shearing(tab);
	float4	p = (float4){2, 3, 4, 0};
	float4	aim = (float4){2, 3, 6, 0};
	p = matrix_tuple_mult(transf, p);
	cr_expect(same_tuple(p, aim) == 1);
}
Test(matrix, shearing6)
{
	float	tab[6] = {0, 0, 0, 0, 0, 1};
	t_m4x4_f 	transf = shearing(tab);
	float4	p = (float4){2, 3, 4, 0};
	float4	aim = (float4){2, 3, 7, 0};
	p = matrix_tuple_mult(transf, p);
	cr_expect(same_tuple(p, aim) == 1);
}

// t_m4x4_f	chained_transfo(t_m4x4_f one, t_m4x4_f two, t_m4x4_f three)
// {
// 	t_m4x4_f	res;

// 	res = matrix_mult(three, two);
// 	res = matrix_mult(res, one);
// 	return (res);
// }

Test(matrix, chaining)
{
	float4 p = (float4){1, 0, 1, 1};
	t_m4x4_f	A = rotation_x(M_PI / 2);
	t_m4x4_f	B = scaling(5, 5, 5);
	t_m4x4_f	C = translation(10, 5, 7);

	float4 p2 = matrix_tuple_mult(A, p);
	float4 p2aim = (float4){1, -1, 0, 1};
	cr_expect(same_tuple(p2, p2aim) == 1);

	float4 p3 = matrix_tuple_mult(B, p2);
	float4 p3aim = (float4){5, -5, 0, 1};
	cr_expect(same_tuple(p3, p3aim) == 1);

	float4 p4 = matrix_tuple_mult(C, p3);
	float4 p4aim = (float4){15, 0, 7, 1};
	// printf("%f, %f, %f, %f\n", p4.x, p4.y, p4.z, p4.w);
	cr_expect(same_tuple(p4, p4aim) == 1);

	t_m4x4_f	fuse = chained_transfo(A, B, C);
	float4	pres = matrix_tuple_mult(fuse, p);
	cr_expect(same_tuple(pres, p4aim) == 1);
}
