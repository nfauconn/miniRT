/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:30:09 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2022/12/16 13:34:00 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

/* !!!! no ID cf init_sphere */
int	set_plan(t_scene *scene, char **params)
{
	int		ret;
	t_elem		*newplan;

	if (ft_strarraysize(params) != 4)
		return (error_display("wrong number of elements for plan"));
	newplan = ft_calloc(1, sizeof(t_elem));
	if (!newplan)
		return (error_display("malloc error"));
	ret = 0;
	if (conv_pos(params[1], newplan, params[0])
		|| conv_orientation(params[2], newplan, params[0])
		|| conv_rgb(params[3], newplan, params[0]))
		ret = 1;
	elem_add_back(&scene->objs, newplan);
	return (ret);
}