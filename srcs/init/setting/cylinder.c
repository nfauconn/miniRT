/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:33:13 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2022/12/16 13:33:30 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

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
	elem_add_back(&scene->objs, newcylinder);
	return (ret);
}