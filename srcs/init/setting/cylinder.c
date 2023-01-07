/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:33:13 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/07 18:13:21 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

// t_m4x4_f	rotate_mat(t_elem	*s)
// {
// 	t_m4x4_f	res;
// 	float	x = s->orientation.x;
// 	float	y = s->orientation.y;
// 	float	z = s->orientation.z;

// 	res = identity_matr;
// 	res[0][0] = x * x * (1 - cos)
// 	res[0][1] = 
// 	res[0][2] = 
// 	res[1][0] = 
// 	res[1][1] = 
// 	res[1][2] = 
// 	res[2][0] = 
// 	res[2][1] = 
// 	res[2][2] = 
// 	return (res);
// }

t_m4x4_f	fuse_rotate(t_elem	*s)
{
	// t_m4x4_f	matrix;
	// t_m4x4_f	matrix1;
	// t_m4x4_f	matrix2;
	t_m4x4_f	matrix3;

	// matrix1 = rotation_x((M_PI * s->orientation.x) / 2);
	// matrix2 = rotation_y((M_PI * s->orientation.y) / 2);
	matrix3 = rotation_z((M_PI * s->orientation.z) / 2);
	// matrix = matrix1 * matrix2 * matrix3;
	return (matrix3);
}
// void	init_cylinder(t_elem *s)
// {
// 	static ssize_t	no = -1;
// 	// float	tab[6] = {0, s->orientation.z, 0, -s->orientation.z, 0, 0};
// 	no++;
// 	s->id.shape = cylinder;
// 	s->id.no = no;
// 	s->o_pos = create_point(0, 0, 0);

// 	t_m4x4_f	rotate_mat;
// 	t_m4x4_f	translate_mat;
// 	t_m4x4_f	scale_mat;

// 	rotate_mat = fuse_rotate(s);
// 	scale_mat = scaling(s->specs.diam_hght[0], s->specs.diam_hght[1], s->specs.diam_hght[0]);
// 	translate_mat = translation(s->w_pos.x, s->w_pos.y, s->w_pos.z);
// 	s->transform = translate_mat * (scale_mat * (rotate_mat));
// 	s->material = default_material(s);
// }
void	init_cylinder(t_elem *s)
{
	static ssize_t	no = -1;
	// float	tab[6] = {0, s->orientation.z, 0, -s->orientation.z, 0, 0};
	no++;
	s->id.shape = cylinder;
	s->id.no = no;
	s->o_pos = create_point(0, 0, 0);
	t_m4x4_f	rotate_matrix;
	rotate_matrix = fuse_rotate(s);
	s->transform = identity_matr();
	s->transform = rotate_matrix;
	// s->transform = s->transform * translation(s->w_pos.x, s->w_pos.y, s->w_pos.z);
	// s->transform = s->transform * scaling(s->specs.diam_hght[0], s->specs.diam_hght[1], s->specs.diam_hght[0]);
	s->material = default_material(s);
}

/* !!!! no ID cf init_sphere */
int	set_cylinder(t_scene *scene, char **params)
{
	int		ret;
	t_elem		*newcylinder;

	if (ft_strarraysize(params) != 6)
		return (error_display("wrong number of elements for cylinder"));
	newcylinder = ft_calloc(1, sizeof(t_elem));
	if (!newcylinder)
		return (error_display("malloc error"));
	ret = 0;
	if (conv_pos(params[1], newcylinder, params[0])
		|| conv_orientation(params[2], newcylinder, params[0])
		|| conv_diam_height(params[3], params[4], newcylinder, params[0])
		|| conv_rgb(params[5], newcylinder, params[0]))
		ret = 1;
	init_cylinder(newcylinder);
	elem_add_back(&scene->objs, newcylinder);
	return (ret);
}