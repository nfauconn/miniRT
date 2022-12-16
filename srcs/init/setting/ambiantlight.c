/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiantlight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:30:51 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2022/12/16 13:35:07 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

int	set_ambiantlight(t_scene *scene, char **params)
{
	if (ft_strarraysize(params) != 3)
		return (error_display("wrong number of elements for ambiant light"));
	if (scene->amblight)
		return (error_display("can be only one ambiant light"));
	scene->amblight = ft_calloc(1, sizeof(t_elem));
	if (!scene->amblight)
		return (error_display("malloc error"));
	if (conv_ratio(params[1], scene->amblight, params[0])
		|| conv_rgb(params[2], scene->amblight, params[0]))
		return (1);
	return (0);
}
