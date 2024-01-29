/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightsource.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:30:47 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/12 16:41:58 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

int	set_lights(t_scene *scene, char **params)
{
	int		ret;
	t_elem	*newlight;

	if (ft_strarraysize(params) != 4)
		return (error_display("wrong number of elements for light"));
	newlight = ft_calloc(1, sizeof(t_elem));
	if (!newlight)
		return (error_display("malloc error"));
	ret = 0;
	if (conv_pos(params[1], newlight, params[0])
		|| conv_ratio(params[2], newlight, params[0])
		|| conv_rgb(params[3], newlight, params[0]))
		ret = 1;
	newlight->color *= newlight->specs.ratio;
	elem_add_back(&scene->lights, newlight);
	return (ret);
}
