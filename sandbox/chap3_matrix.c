/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chap3_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:12:44 by rokerjea          #+#    #+#             */
/*   Updated: 2022/11/16 21:04:16 by rokerjea         ###   ########.fr       */
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
typedef float	t_matrix9	__attribute__((ext_vector_type(16)));
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
		res[i] = dot_product(line, tup);
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