/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:19:07 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/09 16:35:07 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_bool	check_rgb_range(t_rgb color)
{
	t_bool	ret;

	if (color.x >= 0 && color.x <= 255
		&& color.y >= 0 && color.y <= 255
		&& color.x >= 0 && color.z <= 255)
		ret = 0;
	else
		ret = error_display("wrong rgb value");
	return (ret);
}

t_bool	convert_rgb(char *s, t_element *elem)
{
	t_bool	ret;
	char	**rgb;

	rgb = ft_split(s, ',');
	if (!rgb)
		return (error_display("malloc error"));
	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		ret = error_display("wrong rgb value");
	else
	{
		elem->color.x = atof(rgb[0]);
		elem->color.y = atof(rgb[1]);
		elem->color.z = atof(rgb[2]);
		ret = check_rgb_range(elem->color);
	}
	ft_strarrayclear(&rgb);
	return (ret);
}

static t_bool	check_orientation_range(t_vector v)
{
	t_bool	ret;

	if (v.x >= 0.0 && v.x <= 1.0
		&& v.y >= 0.0 && v.y <= 1.0
		&& v.z >= 0.0 && v.z <= 1.0)
		ret = 0;
	else
		ret = error_display("wrong orientation range");
	return (ret);
}

t_bool	convert_orientation(char *s, t_element *elem)
{
	t_bool	ret;
	char	**or;

	or = ft_split(s, ',');
	if (!or)
		return (error_display("malloc error"));
	if (!or[0] || !or[1] || !or[2] || or[3])
		ret = error_display("wrong orientation value");
	else
	{
		elem->orientation.x = atof(or[0]);
		elem->orientation.y = atof(or[1]);
		elem->orientation.z = atof(or[2]);
		ret = check_orientation_range(elem->orientation);
	}
	return (ret);
}

t_bool	convert_pos(char *s, t_element *elem)
{
	t_bool	ret;
	char	**pos;

	pos = ft_split(s, ',');
	if (!pos)
		return (error_display("malloc error"));
	if (!pos[0] || !pos[1] || !pos[2] || pos[3])
		ret = error_display("wrong pos value");
	else
	{
		elem->pos.x = atof(pos[0]);
		elem->pos.y = atof(pos[1]);
		elem->pos.z = atof(pos[2]);
		ret = 0;
	}
	ft_strarrayclear(&pos);
	return (ret);
}