/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 15:18:49 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/13 17:16:06 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "externlibs.h"
# include "tuple.h"

/* MATR_CREA */
t_m4x4_f	matrix_4xf_create(float *f);
t_m3x3_f	matrix_3xf_create(float *f);
t_m4x4_f	identity_matr(void);

/* MATRIX_MULT */
t_m4x4_f	matrix_mult(t_m4x4_f matrix, t_m4x4_f matrix2);
t_float4	get_vline(int i, t_m4x4_f matrix); // static ?
t_float4	get_vcol(int i, t_m4x4_f matrix2);
float		dot_product_ma(t_m4x4_f mat1, int line, t_m4x4_f mat2, int col);

/* MATRIX_TRANSFORM */
t_m4x4_f	translation(float x, float y, float z);
t_m4x4_f	scaling(float x, float y, float z);
t_m4x4_f	rotation_x(float angle);
t_m4x4_f	rotation_y(float angle);
t_m4x4_f	rotation_z(float angle);

/* MATRIX_INVERSE */
float		cofactor(t_m3x3_f matrix, int line, int col);
t_m4x4_f	cofactor_matrix(t_m4x4_f matr);
float		cofactor4x(t_m4x4_f matrix, int line, int col);
t_m4x4_f	divide_matr_by_scalar(t_m4x4_f res, float deter);
t_m4x4_f	inverse(t_m4x4_f matr);

/* MX_ SUBMATRIX */
t_m3x3_f	submatrix4_to_3(t_m4x4_f matr, int line, int col);
t_float4	submatrix3_to_2(t_m3x3_f matr, int line, int col);
float		determinant3x3(t_m3x3_f matrix);
float		determinant_4xf(t_m4x4_f matrix);

/* MATRIX_UTILS */
t_m4x4_f	transpose(t_m4x4_f matrix);
float		determinant2x2(t_float4 matrix);
t_float4	matrix_tuple_mult(t_m4x4_f matrix, t_float4 tup);

#endif