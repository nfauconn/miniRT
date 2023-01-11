/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:30:09 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/11 14:28:20 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

t_m4x4_f	pl_transform_matr(t_elem *pl)
{
	t_m4x4_f	res;

	res = translation(pl->w_pos.x, pl->w_pos.y, pl->w_pos.z);
	res = matrix_mult(res, \
					rotation_x(M_PI * pl->orientation.x));
	res = matrix_mult(res, \
					rotation_y(M_PI * pl->orientation.y));
	res = matrix_mult(res, \
					rotation_z(M_PI * pl->orientation.z));
	return (res);
}

void	init_plane(t_elem *pl)
{
	pl->shape = plane;
	pl->o_pos = create_point(0, 0, 0);
	pl->transform = pl_transform_matr(pl);
	pl->material = default_material(pl);
}

int	set_plane(t_scene *scene, char **params)
{
	int			ret;
	t_elem		*newplane;

	if (ft_strarraysize(params) != 4)
		return (error_display("wrong number of elements for plane"));
	newplane = ft_calloc(1, sizeof(t_elem));
	if (!newplane)
		return (error_display("malloc error"));
	ret = 0;
	if (conv_pos(params[1], newplane, params[0])
		|| conv_orientation(params[2], newplane, params[0])
		|| conv_rgb(params[3], newplane, params[0]))
		ret = 1;
	elem_add_back(&scene->objs, newplane);
	init_plane(newplane);
	return (ret);
}