/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_to_tuple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noe <noe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:19:07 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/10 15:58:01 by noe              ###   ########.fr       */
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
		ret = 1;
	return (ret);
}

t_bool	conv_rgb(char *s, t_element *elem, char *elem_name)
{
	t_bool	ret;
	char	**rgb;

	rgb = ft_split(s, ',');
	if (!rgb)
		return (error_display("malloc error"));
	ret = 0;
	if (ft_strarraysize(rgb) != 3)
		ret = error_display2("wrong rgb value for ", elem_name);
	else
	{
		elem->color.x = atof(rgb[0]);
		elem->color.y = atof(rgb[1]);
		elem->color.z = atof(rgb[2]);
		if (check_rgb_range(elem->color))
			ret = error_display2("wrong rgb value for ", elem_name);
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
		ret = 1;
	return (ret);
}

t_bool	conv_orientation(char *s, t_element *elem, char *elem_name)
{
	t_bool	ret;
	char	**or;

	or = ft_split(s, ',');
	if (!or)
		return (error_display("malloc error"));
	ret = 0;
	if (ft_strarraysize(or) != 3)
		ret = error_display2("wrong orientation value for ", elem_name);
	else
	{
		elem->orientation.x = atof(or[0]);
		elem->orientation.y = atof(or[1]);
		elem->orientation.z = atof(or[2]);
		if (check_orientation_range(elem->orientation))
			ret = error_display2("wrong orientation range for ", elem_name);
	}
	ft_strarrayclear(&or);
	return (ret);
}

t_bool	conv_pos(char *s, t_element *elem, char *elem_name)
{
	t_bool	ret;
	char	**pos;

	pos = ft_split(s, ',');
	if (!pos)
		return (error_display("malloc error"));
	if (ft_strarraysize(pos) != 3)
		ret = error_display2("wrong pos value for ", elem_name);
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