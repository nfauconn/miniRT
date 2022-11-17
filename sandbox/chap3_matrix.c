/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chap3_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:12:44 by rokerjea          #+#    #+#             */
/*   Updated: 2022/11/17 18:10:50 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/mnt/nfs/homes/rokerjea/sgoinfre/Criterion/include/criterion/criterion.h"
# include <math.h>
# include <stdio.h>
# include <signal.h>
# include <errno.h>

typedef float	float16	__attribute__((ext_vector_type(16)));
typedef int	int16	__attribute__((ext_vector_type(16)));
typedef float	t_matrix4	__attribute__((ext_vector_type(16)));
typedef float	t_matrix3	__attribute__((ext_vector_type(16)));
// typedef int	int9	__attribute__((ext_vector_type(9)));
typedef float float4 __attribute__((ext_vector_type(4)));
typedef int	int4 __attribute__((ext_vector_type(4)));

bool	same_float(float f1, float f2)
{
	float	epsilon;

	epsilon = 0.00001;
	if (fabs(f1 - f2) > epsilon)
		return (0);
	return (1);
}

int	any_matrix(int16 bool_matrix)
{
	if (!bool_matrix.s0 || !bool_matrix.s1 || !bool_matrix.s2 || !bool_matrix.s3
		|| !bool_matrix.s4 || !bool_matrix.s5 || !bool_matrix.s6 || !bool_matrix.s7
		|| !bool_matrix.s8 || !bool_matrix.s9 || !bool_matrix.sa || !bool_matrix.sb
		|| !bool_matrix.sc || !bool_matrix.sd || !bool_matrix.se || !bool_matrix.sf)
		return (0);
	return (1);
}

bool	same_matrix(float16 matrix1, float16 matrix2)
{
	int16	bool_mat;
	int	sum;
	bool_mat = matrix1 == matrix2;
	// printf("%d\n", bool_mat.s0);
	sum = any_matrix(bool_mat);
	return (sum);
}

Test(matrix, matrix_create)
{
	float16 matrix = (float16){1, 2, 3, 4, 5.5, 6.5, 7.5, 8.5, 9, 10, 11, 12, 13.5, 14.5, 15.5, 16.5};
	//printf ("%f\n", matrix.s1);
	cr_expect(same_float(matrix.s0, 1) == 1);
	cr_expect(same_float(matrix.s3, 4) == 1);
	cr_expect(same_float(matrix.s4, 5.5) == 1);
	cr_expect(same_float(matrix.s6, 7.5) == 1);
	cr_expect(same_float(matrix.sa, 11) == 1);
	cr_expect(same_float(matrix.sc, 13.5) == 1);
	cr_expect(same_float(matrix.se, 15.5) == 1);
	cr_expect(same_float(matrix.sf, 16.5) == 1);
}

Test(matrix, matrix_compare)
{
	float16 matrix = (float16){1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
	float16 matrix2 = (float16){1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
	cr_expect(same_matrix(matrix, matrix2) == 1);
	matrix2 = (float16){1.5, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 15};
	cr_expect(same_matrix(matrix, matrix2) == 0);
}

float	dot_product(float4 tup1, float4 tup2)
{
	return ((tup1.x * tup2.x) \
		+ (tup1.y * tup2.y) \
		+ (tup1.z * tup2.z) \
		+ (tup1.w * tup2.w));
}

// float4	get_line(float16 matrix, int line)
// {
// 	float4	res;
	
// 	if (line / 4 == 0)
// 		res = matrix.s0123;
// }

float4	get_vline(int i, float16 matrix)
{
	if (i < 4)
		return (matrix.s0123);
	else if (i < 8)
		return (matrix.s4567);
	else if (i < 12)
		return (matrix.s89ab);
	else
		return (matrix.scdef);
}

float4	get_vcol(int i, float16 matrix2)
{
	if (i % 4 == 0)
		return (matrix2.s048c);
	else if (i % 4 == 1)
		return (matrix2.s159d);
	else if (i % 4 == 2)
		return (matrix2.s26ae);
	else
		return (matrix2.s37bf);
}

float16	matrix_mult(float16 matrix, float16 matrix2)
{
	float4	line;
	float4	col;
	float16	res;
	int	i;

	i = 0;
	while (i < 16)
	{
		line = get_vline(i, matrix);
		col = get_vcol(i, matrix2);
		res[i] = dot_product(line, col);
		i++;
	}
	return (res);
}

Test(matrix, matrix_mult)
{
	float16 matrix = (float16){1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
	float16 matrix2 = (float16){-2, 1, 2, 3, 3, 2, 1, -1, 4, 3, 6, 5, 1, 2, 7, 8};
	float	test;
	test = dot_product(matrix.s89ab, matrix2.s37bf);
	cr_expect(same_float(test, 102) == 1, "internal step of matrix multiplication");
	float16 matrix3 = matrix_mult(matrix, matrix2);
	float16 matrix4 = (float16){20, 22, 50, 48, 44, 54, 114, 108, 40, 58, 110, 102, 16, 26, 46, 42};
	cr_expect(same_matrix(matrix3, matrix4) == 1, "multiplication of full matrix");
}

bool	same_tuple(float4 tup1, float4 tup2)
{
	float	epsilon;

	epsilon = 0.00001;
	if (fabs(tup1.x - tup2.x) > epsilon || fabs(tup1.y - tup2.y) > epsilon
		|| fabs(tup1.z - tup2.z) > epsilon || fabs(tup1.w - tup2.w) > epsilon)
		return (0);
	return (1);
}

float4	matrix_tuple_mult(float16 matrix, float4 tup)
{
	float4	res;
	float4	line;
	int	i;

	i = 0;
	while (i < 16)
	{
		line = get_vline(i, matrix);
		res[i / 4] = dot_product(line, tup);
		i += 4;
	}
	return (res);
}

Test(matrix, matrix_tuple_mult)
{
	float16 matrix = (float16){1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1};
	float4	tup = (float4){1, 2, 3, 1};
	float4	res = (float4){18, 24, 33, 1};
	float4	test = matrix_tuple_mult(matrix, tup);
	// printf("%f %f %f %f\n", test.x, test.y, test.z, test.w);
	// printf("%f %f %f %f\n", res.x, res.y, res.z, res.w);
	cr_expect(same_tuple(test, res) == 1, "multiplication of matrix by tuple");
}

Test(matrix, identity_matrix)
{
	float16 matrix = (float16){1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
	float16 matrix2 = (float16){1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	float16	test;
	test = matrix_mult(matrix, matrix2);
	cr_expect(same_matrix(test, matrix) == 1, "identity mtrx multi");
	float4	res = (float4){18, 24, 33, 1};
	float4	test2 = matrix_tuple_mult(matrix2, res);
	cr_expect(same_tuple(test2, res) == 1, "multiplication of identity mtrx by tuple");
}

float16	matrix_transpose(float16 matrix)
{
	float16	res;
	res.s048c = matrix.s0123;
	res.s159d = matrix.s4567;
	res.s26ae = matrix.s89ab;
	res.s37bf = matrix.scdef;
	return (res);
}

Test(matrix, transposing_matrix)
{
	float16 matrix = (float16){0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8};
	float16 matrixres;
	float16 matrixaim = (float16){0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8};
	matrixres = matrix_transpose(matrix);
	cr_expect(same_matrix(matrixres, matrixaim) == 1);
	float16 matrixaim2 = (float16){0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 5, 8};
	cr_expect(same_matrix(matrixres, matrixaim2) == 0);
	float16 matrix2 = (float16){1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	float16 matrixres2 = matrix_transpose(matrix2);
	cr_expect(same_matrix(matrixres2, matrix2) == 1);
}

float	determinant2x2(float4 matrix)
{
	float	res;
	
	res = matrix.x * matrix.w - matrix.y * matrix.z;
	return (res);
}

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

float4	submatrix3_to_2(t_matrix3 matr, int line, int col)
{
	float4	res;
	int	i;
	int	j;
	float	tab[9] = {matr.s0, matr.s1, matr.s2, matr.s3, matr.s4, matr.s5,
		matr.s6, matr.s7, matr.s8};
	j = 0;
	i = 0;
	while(i < 4)
	{
		if (isnotinline(j, line) && isnotincol(j, col))
		{
			if (i == 0)
				res.x = tab[j];
			if (i == 1)
				res.y = tab[j];
			if (i == 2)
				res.z = tab[j];
			if (i == 3)
				res.w = tab[j];
			i++;
		}
		j++;
	}
	return (res);
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

t_matrix3	convert_tab_to_matr_3x3(float	tab[9])
{
	t_matrix3	res;
	// float	tabres[9] = {res.s0, res.s1, res.s2, res.s3,
	// 	res.s4, res.s5, res.s6, res.s7, res.s8};
	int	i;

	i = 0;
	while (i < 9)
	{
		res[i] = tab[i];
		// printf ("%f, ", tabres[i]);
		i++;
	}
	// printf("\n");
	return (res);
}

t_matrix3	submatrix4_to_3(t_matrix4 matr, int line, int col)
{
	t_matrix3	res;
	int	i;
	int	j;
	// float	tabres[9];
	float	tab[16] = {matr.s0, matr.s1, matr.s2, matr.s3, matr.s4, matr.s5,
		matr.s6, matr.s7, matr.s8, matr.s9, matr.sa, matr.sb, matr.sc, matr.sd,
		matr.se, matr.sf};
	j = 0;
	i = 0;
	// printf ("%f\n", tab[0]);
	// printf ("%f\n", tab[j]);
	while(i < 9)
	{
		// printf ("%f\n", tab[j]);
		if (isnotinline_4x4(j, line) && isnotincol_4x4(j, col))
		{
			res[i] = tab[j];
			i++;
		}
		j++;
	}
	// res = convert_tab_to_matr_3x3(tabres);
	// printf ("%f\n", res.s0);
	return (res);
}

Test(matrix, submatrix)
{
	t_matrix3	matrix = (t_matrix3){1, 5, 0, -3, 2, 7, 0, 6, -3};
	float4		aim = (float4){-3, 2, 0, 6};
	float4		res = submatrix3_to_2(matrix, 0, 2);
	cr_expect(same_tuple(aim, res) == 1);
}

// int	any_matrix_3x3(int9 bool_matrix)
// {
// 	if (!bool_matrix.s0 || !bool_matrix.s1 || !bool_matrix.s2 || !bool_matrix.s3
// 		|| !bool_matrix.s4 || !bool_matrix.s5 || !bool_matrix.s6 || !bool_matrix.s7
// 		|| !bool_matrix.s8)
// 		return (0);
// 	return (1);
// }

bool	same_matrix_3x3(t_matrix3 matrix1, t_matrix3 matrix2)
{
	if (matrix1.s0 != matrix2.s0 || matrix1.s1 != matrix2.s1
	|| matrix1.s2 != matrix2.s2 || matrix1.s3 != matrix2.s3
	|| matrix1.s4 != matrix2.s4 || matrix1.s5 != matrix2.s5
	|| matrix1.s6 != matrix2.s6 || matrix1.s7 != matrix2.s7
	|| matrix1.s8 != matrix2.s8)
		return (0);
	return (1);
}

Test(matrix, submatrix2)
{
	t_matrix4	matrix = (t_matrix4){-6, 1, 1, 6, -8, 5, 8, 6, -1, 0, 8, 2, -7, 1, -1, 1};
	t_matrix3	aim = (t_matrix3){-6, 1, 6, -8, 8, 6, -7, -1, 1};
	t_matrix3	res = submatrix4_to_3(matrix, 2, 1);
	// printf ("%f, %f\n", res.s0, aim.s0);
	cr_expect(same_matrix_3x3(aim, res) == 1);
}

float	minor_of_3x3(t_matrix3 matrix, int line, int col)
{
	float4	sub;

	sub = submatrix3_to_2(matrix, line, col);
	return (determinant2x2(sub));
}

Test(matrix, minor)
{
	t_matrix3	matrix = (t_matrix3){3, 5, 0, 2, -1, -7, 6, -1, 5};
	float4		sub = submatrix3_to_2(matrix, 1, 0);
	float		determinant = determinant2x2(sub);
	cr_expect(same_float(determinant, 25) == 1);
	float		determinant2 = minor_of_3x3(matrix, 1, 0);
	cr_expect(same_float(determinant2, 25) == 1);
	cr_expect(same_float(determinant2, 24) == 0);	
}

float	cofactor(t_matrix3 matrix, int line, int col)
{
	float4	sub;
	float	res;

	sub = submatrix3_to_2(matrix, line, col);
	res = determinant2x2(sub);
	if (line + col % 2 == 1)
		res *= -1;
	return (res);
}

Test(matrix, cofactor)
{
	t_matrix3	matrix = (t_matrix3){3, 5, 0, 2, -1, -7, 6, -1, 5};
	float	minor = -12;
	float	cofactortest = cofactor(matrix, 0, 0);
	cr_expect(same_float(minor, cofactortest) == 1);
	cofactortest = cofactor(matrix, 1, 0);
	cr_expect(same_float(-25, cofactortest) == 1);
}

float	determinant3x3(t_matrix3 matrix)
{
	float	res;
	
	res = matrix.s0 * cofactor(matrix, 0, 0);
	res += matrix.s1 * cofactor(matrix, 0, 1);
	res += matrix.s2 * cofactor(matrix, 0, 2);
	return (res);
}

Test(matrix, determinant3x3)
{
	t_matrix3	matrix = (t_matrix3){1, 2, 6, -5, 8, -4, 2, 6, 4};
	float	cofactor1 = cofactor(matrix, 0, 0);
	float	cofactor2 = cofactor(matrix, 0, 1);
	float	cofactor3 = cofactor(matrix, 0, 2);
	cr_expect(same_float(56, cofactor1) == 1);
	cr_expect(same_float(12, cofactor2) == 1);
	cr_expect(same_float(-46, cofactor3) == 1);
	float	determinanttest = determinant3x3(matrix);
	cr_expect (same_float(determinanttest, -196) == 1);
}

float	cofactor4x(t_matrix4 matrix, line, col)
{
	t_matrix3	sub;
	float	res;

	sub = submatrix4_to_3(matrix, line, col);
	res = determinant3x3(sub);
	if (line + col % 2 == 1)
		res *= -1;
	return (res);
}

Test(matrix, determinant4x4)
{
	t_matrix4 matrix = (t_matrix4){-2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9};
	float	cofactor1 = cofactor4x(matrix, 0, 0);
	float	cofactor2 = cofactor4x(matrix, 0, 1);
	float	cofactor3 = cofactor4x(matrix, 0, 2);
	float	cofactor4 = cofactor4x(matrix, 0, 3);
	cr_expect(same_float(690, cofactor1) == 1);
	cr_expect(same_float(447, cofactor2) == 1);
	cr_expect(same_float(210, cofactor3) == 1);
	cr_expect(same_float(51, cofactor4) == 1);	
}