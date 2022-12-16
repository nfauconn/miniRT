/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:30:09 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2022/12/16 17:39:19 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

void	init_plane(t_elem *pl)
{
	static ssize_t	no = -1;

	no++;
	pl->id.shape = plane;
	pl->id.no = no;
	pl->o_pos = create_point(0, 0, 0);
	pl->transform = identity_matr();
	pl->material = default_material(pl);
}

int	set_plane(t_scene *scene, char **params)
{
	int		ret;
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
	return (ret);
}