/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:18:49 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/14 17:16:32 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "extern_libs.h"
# include "tuple.h"

/* CREATION */
t_m4x4_f	matrix_4xf_create(float *f);
t_m3x3_f	matrix_3xf_create(float *f);
t_m4x4_f	identity_matr(void);

/* SUBMATRIX */
t_m3x3_f	submatrix4_to_3(t_m4x4_f matr, int line, int col);
t_float4	submatrix3_to_2(t_m3x3_f matr, int line, int col);

/* COMPAR */
bool		same_matrix(t_m4x4_f matrix1, t_m4x4_f matrix2);
bool		same_matrix_3x3(t_m3x3_f matrixaim, t_m3x3_f res);

/* MATHS */
float		dot_product_ma(t_m4x4_f matrix, int line, t_m4x4_f matrix2, int col);
t_m4x4_f	matrix_mult(t_m4x4_f matrix, t_m4x4_f matrix2);
t_float4	matrix_tuple_mult(t_m4x4_f matrix, t_float4 tup);
t_m4x4_f	divide_matr_by_scalar(t_m4x4_f res, float deter);

/* ??? */
t_float4	get_vline(int i, t_m4x4_f matrix);
t_float4	get_vcol(int i, t_m4x4_f matrix2);
t_m4x4_f	transpose(t_m4x4_f matrix);
float		determinant2x2(t_float4 matrix);
int			isnotinline(int	j, int line);
int			isnotincol(int	j, int col);
int			isnotinline_4x4(int	j, int line);
int			isnotincol_4x4(int	j, int col);
void		printf_3fmatr(t_m3x3_f	matrixaim);
float		minor_of_3x3(t_m3x3_f matrix, int line, int col);
float		cofactor(t_m3x3_f matrix, int line, int col);
float		determinant3x3(t_m3x3_f matrix);
float		cofactor4x(t_m4x4_f matrix, int line, int col);
float		determinant_4xf(t_m4x4_f matrix);
bool		is_matrice_invertible(t_m4x4_f matrix);;
t_m4x4_f	cofactor_matrix(t_m4x4_f matr);
void		printf_4fmatr(t_m4x4_f	matrixaim);
t_m4x4_f	inverse(t_m4x4_f matr);
t_m4x4_f	translation(float x, float y, float z);
t_m4x4_f	scaling(float x, float y, float z);
t_m4x4_f	rotation_x(float angle);
t_m4x4_f	rotation_y(float angle);
t_m4x4_f	rotation_z(float angle);
t_m4x4_f	shearing(float	*tab);
t_m4x4_f	chained_transfo(t_m4x4_f one, t_m4x4_f two, t_m4x4_f three);

#endif