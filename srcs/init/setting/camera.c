/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:30:55 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/15 20:27:18 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

static bool	conv_camorientation(char *s, t_camera *cam, char *elem_name)
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
		if (cam->orientation.z == 0)
			cam->orientation.z = EPSILON;
		cam->orientation.w = 0;
		if (check_orientation_range(cam->orientation))
			ret = error_display2("wrong orientation range for ", elem_name);
	}
	ft_strarrayclear(&or);
	return (ret);
}

static bool	conv_campos(char *s, t_camera *cam, char *elem_name)
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

void	init_camera(t_camera *cam, float hsize, float vsize)
{
	float		half_view;
	float		aspect_ratio;

	cam->hsize = hsize;
	cam->vsize = vsize;
	cam->transform = identity_matr();
	half_view = tan(cam->fov / 2);
	aspect_ratio = cam->hsize / cam->vsize;
	if (aspect_ratio >= 1)
	{
		cam->half_width = half_view;
		cam->half_height = half_view / aspect_ratio;
	}
	else
	{
		cam->half_width = half_view * aspect_ratio;
		cam->half_height = half_view;
	}
	cam->pixel_size = (cam->half_width * 2) / cam->hsize;
}

int	set_camera(t_scene *scene, char **params)
{
	if (ft_strarraysize(params) != 4)
		return (error_display("wrong number of elements for camera"));
	if (scene->cam)
		return (error_display("can be only one camera"));
	scene->cam = ft_calloc(1, sizeof(t_elem));
	if (!scene->cam)
		return (error_display("malloc error"));
	if (conv_campos(params[1], scene->cam, params[0])
		|| conv_camorientation(params[2], scene->cam, params[0])
		|| conv_fov(params[3], scene->cam, params[0]))
		return (1);
	scene->cam->fov *= M_PI / 180;
	init_camera(scene->cam, WIDTH, HEIGHT);
	change_cam_transform_matr(scene->cam);
	return (0);
}
