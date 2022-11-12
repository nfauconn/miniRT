/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_to_tuple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:19:07 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/12 13:23:28 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* static t_bool	check_rgb_range(t_rgb color)
{
	t_bool	ret;

	if (color.x >= 0 && color.x <= 255
		&& color.y >= 0 && color.y <= 255
		&& color.x >= 0 && color.z <= 255)
		ret = 0;
	else
		ret = 1;
	return (ret);
} */ //inoperant bc t_rgb are unsigned char

t_bool	conv_rgb(char *s, t_element *elem, char *elem_name)
{
	t_bool		ret;
	char		**rgb;

	rgb = ft_split(s, ',');
	if (!rgb)
		return (error_display("malloc error"));
	ret = 0;
	if (ft_strarraysize(rgb) != 3)
		ret = error_display2("wrong rgb value for ", elem_name);
	else
	{
		elem->color.x = (uint8_t)ft_atoi(rgb[0]);
		elem->color.y = (uint8_t)ft_atoi(rgb[1]);
		elem->color.z = (uint8_t)ft_atoi(rgb[2]);
	/* 	if (check_rgb_range(elem->color))
			ret = error_display2("wrong rgb value for ", elem_name); */
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
		elem->orientation.x = ft_atof(or[0]);
		elem->orientation.y = ft_atof(or[1]);
		elem->orientation.z = ft_atof(or[2]);
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
		elem->pos.x = ft_atof(pos[0]);
		elem->pos.y = ft_atof(pos[1]);
		elem->pos.z = ft_atof(pos[2]);
		ret = 0;
	}
	ft_strarrayclear(&pos);
	return (ret);
}