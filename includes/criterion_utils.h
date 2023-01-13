#ifndef CRITERION_UTILS_H
# define CRITERION_UTILS_H

# define WHITE {1, 1, 1, 0}

#include "criterion_header.h"
#include "minirt.h"
#include "tuple.h"
#include "matrix.h"
#include "ray.h"
#include "lights.h"
#include "scene.h"
#include "inter.h"
#include "setup.h"

bool		same_tuple(t_float4 tup1, t_float4 tup2);
bool		tuple_bool(t_int4 tuple);
bool		same_float(float f1, float f2);

t_m4x4_f	shearing(float	*tab);//
bool		same_matrix(t_m4x4_f matrix1, t_m4x4_f matrix2);
bool		same_matrix_3x3(t_m3x3_f matrixaim, t_m3x3_f res);//
void		printf_3fmatr(t_m3x3_f matrixaim);//
void		printf_4fmatr(t_m4x4_f	matrixaim);
bool		is_matrice_invertible(t_m4x4_f matrix);//
float		minor_of_3x3(t_m3x3_f matrix, int line, int col);//
int			isnotinline(int j, int line);//
int			isnotincol(int j, int col);//
int			isnotinline_4x4(int j, int line);//
int			isnotincol_4x4(int j, int col);//
t_m4x4_f	chained_transfo(t_m4x4_f one, t_m4x4_f two, t_m4x4_f three);

void		point_light(t_elem *light, t_point pos, t_rgb color);

#endif