/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_to_tuple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:19:07 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/17 17:05:30 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

static bool	check_rgb_range(t_rgb color)
{
	bool	ret;

	if (color.x >= 0 && color.x <= 255
		&& color.y >= 0 && color.y <= 255
		&& color.x >= 0 && color.z <= 255)
		ret = 0;
	else
		ret = 1;
	return (ret);
}

bool	conv_rgb(char *s, t_elem *elem, char *elem_name)
{
	bool		ret;
	char		**rgb;

	rgb = ft_split(s, ',');
	if (!rgb)
		return (error_display("malloc error"));
	ret = 0;
	if (ft_strarraysize(rgb) != 3)
		ret = error_display2("wrong rgb value for ", elem_name);
	else
	{
		elem->color.x = ft_atof(rgb[0]);
		elem->color.y = ft_atof(rgb[1]);
		elem->color.z = ft_atof(rgb[2]);
		elem->color.w = 0;
	 	if (check_rgb_range(elem->color))
			ret = error_display2("wrong rgb value for ", elem_name);
	}
	elem->color.x = convert_color_to_unit(elem->color.x);
	elem->color.y = convert_color_to_unit(elem->color.y);
	elem->color.z = convert_color_to_unit(elem->color.z);
	ft_strarrayclear(&rgb);
	return (ret);
}

static bool	check_orientation_range(t_vector v)
{
	bool	ret;

	if (v.x >= -1.0 && v.x <= 1.0
		&& v.y >= -1.0 && v.y <= 1.0
		&& v.z >= -1.0 && v.z <= 1.0)
		ret = 0;
	else
		ret = 1;
	return (ret);
}

bool	conv_camorientation(char *s, t_camera *cam, char *elem_name)
{
	bool	ret;
	char	**or;

	or = ft_split(s, ',');
	if (!or)
		return (error_display("malloc error"));
	ret = 0;
	if (ft_strarraysize(or) != 3)
		ret = error_display2("wrong orientation value for ", elem_name);
	else
	{
		cam->orientation.x = ft_atof(or[0]);
		cam->orientation.y = ft_atof(or[1]);
		cam->orientation.z = ft_atof(or[2]);
		cam->orientation.w = 0;
		if (check_orientation_range(cam->orientation))
			ret = error_display2("wrong orientation range for ", elem_name);
	}
	ft_strarrayclear(&or);
	return (ret);
}

bool	conv_orientation(char *s, t_elem *elem, char *elem_name)
{
	bool	ret;
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
		elem->orientation.w = 0;
		if (check_orientation_range(elem->orientation))
			ret = error_display2("wrong orientation range for ", elem_name);
	}
	ft_strarrayclear(&or);
	return (ret);
}

bool	conv_pos(char *s, t_elem *elem, char *elem_name)
{
	bool	ret;
	char	**pos;

	pos = ft_split(s, ',');
	if (!pos)
		return (error_display("malloc error"));
	if (ft_strarraysize(pos) != 3)
		ret = error_display2("wrong pos value for ", elem_name);
	else
	{
		elem->w_pos.x = ft_atof(pos[0]);
		elem->w_pos.y = ft_atof(pos[1]);
		elem->w_pos.z = ft_atof(pos[2]);
		elem->w_pos.w = 1;
		ret = 0;
	}
	ft_strarrayclear(&pos);
	return (ret);
}

bool	conv_campos(char *s, t_camera *cam, char *elem_name)
{
	bool	ret;
	char	**pos;

	pos = ft_split(s, ',');
	if (!pos)
		return (error_display("malloc error"));
	if (ft_strarraysize(pos) != 3)
		ret = error_display2("wrong pos value for ", elem_name);
	else
	{
		cam->w_pos.x = ft_atof(pos[0]);
		cam->w_pos.y = ft_atof(pos[1]);
		cam->w_pos.z = ft_atof(pos[2]);
		cam->w_pos.w = 1;
		ret = 0;
	}
	ft_strarrayclear(&pos);
	return (ret);
}