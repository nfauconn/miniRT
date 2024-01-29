/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_to_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:56:42 by noe               #+#    #+#             */
/*   Updated: 2023/01/04 17:11:51 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

bool	conv_ratio(char *s, t_elem *elem, char *elem_name)
{
	float	ratio;

	ratio = ft_atof(s);
	if (ratio < 0.0 || ratio > 1.0)
		return (error_display2("wrong ratio range for ", elem_name));
	elem->specs.ratio = ratio;
	return (0);
}

bool	conv_fov(char *s, t_camera *cam, char *elem_name)
{
	float	fov;

	fov = ft_atof(s);
	if (fov < 0 || fov > 180)
		return (error_display2("wrong fov range for ", elem_name));
	cam->fov = fov;
	return (0);
}

bool	conv_radius(char *s, t_elem *elem, char *elem_name)
{
	float	diameter;

	diameter = ft_atof(s);
	if (diameter <= 0)
		return (error_display2("wrong radius range for ", elem_name));
	elem->specs.radius = diameter / 2;
	return (0);
}

bool	conv_diam_height(char *s1, char *s2, t_elem *elem, char *elem_name)
{
	float	diam_hght[2];

	diam_hght[0] = ft_atof(s1);
	if (diam_hght[0] <= 0)
		return (error_display2("wrong diameter value for ", elem_name));
	elem->specs.diam_hght[0] = diam_hght[0];
	diam_hght[1] = ft_atof(s2);
	if (diam_hght[1] <= 0)
		return (error_display2("wrong heigth value for ", elem_name));
	elem->specs.diam_hght[1] = diam_hght[1];
	return (0);
}
