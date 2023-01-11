/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:33:13 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/11 18:32:59 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

t_m4x4_f	fuse_rotate(t_elem	*cyl)
{
	t_m4x4_f	matrix;
	t_m4x4_f	matrix1;
	t_m4x4_f	matrix2;
	t_m4x4_f	matrix3;

	matrix1 = rotation_x((M_PI * cyl->orientation.x) / 2);
	matrix2 = rotation_y((M_PI * cyl->orientation.y) / 2);
	matrix3 = rotation_z((M_PI * cyl->orientation.z) / 2);
	matrix = matrix1 * matrix2 * matrix3;
	return (matrix3);
}

t_m4x4_f	cyl_transfo_matr(t_elem *cyl)
{
	t_m4x4_f	res;
	t_m4x4_f	rotate_matrix;

	rotate_matrix = fuse_rotate(cyl);
	res = identity_matr();
	res = rotate_matrix;
	res = res * scaling(cyl->specs.diam_hght[0], 1, cyl->specs.diam_hght[0]);
	res = res * translation(cyl->w_pos.x, cyl->w_pos.y, cyl->w_pos.z);
	return (res);
}

void	init_cylinder(t_elem *cyl)
{
	cyl->shape = cylinder;
	cyl->o_pos = create_point(0, 0, 0);
	cyl->transform = cyl_transfo_matr(cyl);
	cyl->material = default_material(cyl);
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