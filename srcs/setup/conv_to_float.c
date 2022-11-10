/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_to_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:56:42 by noe               #+#    #+#             */
/*   Updated: 2022/11/10 13:37:43 by noe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	conv_ratio(char *s, t_element *elem, char *elem_name)
{
	float ratio;

	ratio = ft_atof(s);
	if (ratio < 0.0 || ratio > 1.0)
		return (error_display2("wrong ratio range for ", elem_name));
	elem->specs.ratio = ratio;
	return (0);
}

t_bool	conv_fov(char *s, t_element *elem, char *elem_name)
{
	float	fov;

	fov = ft_atof(s);
	if (fov < 0 || fov > 180)
		return (error_display2("wrong fov range for ", elem_name));
	elem->specs.fov = fov;
	return (0);
}