/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:33:13 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/04 21:32:59 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

void	init_cylinder(t_elem *s)
{
	static ssize_t	no = -1;
	float	tab[6] = {s->orientation.z, s->orientation.z, 0, -s->orientation.z, 0, 0};
	no++;
	s->id.shape = cylinder;
	s->id.no = no;
	s->o_pos = create_point(0, 0, 0);
	// s->transform = rotation_x(M_PI * s->orientation.x);
	// s->transform = matrix_mult(s->transform, \
	// 				rotation_y(M_PI * s->orientation.y));
	s->transform = shearing(tab);
	s->transform = matrix_mult(s->transform, \
					translation(s->w_pos.x, s->w_pos.y, s->w_pos.z));
	s->transform = matrix_mult(s->transform, \
					scaling(s->specs.diam_hght[0], s->specs.diam_hght[1], s->specs.diam_hght[0]));
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