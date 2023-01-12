/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:30:55 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/12 16:42:44 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

void	init_camera(t_camera *cam, float hsize, float vsize)
{
	float		half_view;
	float		aspect;

	cam->hsize = hsize;
	cam->vsize = vsize;
	cam->transform = identity_matr();
	half_view = tan(cam->fov / 2);
	aspect = cam->hsize / cam->vsize;
	if (aspect >= 1)
	{
		cam->half_width = half_view;
		cam->half_height = half_view / aspect;
	}
	else
	{
		cam->half_width = half_view * aspect;
		cam->half_height = half_view;
	}
	cam->pixel_size = (cam->half_width * 2) / cam->hsize;
}

int	set_camera(t_scene *scene, char **params)
{
	t_point		from;
	t_point		to;
	t_vector	up;
	t_ray		r;

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
	from = scene->cam->w_pos;
	r = ray(from, scene->cam->orientation);
	to = position(r, 1);
	up = create_vector(0, 1, 0);
	scene->cam->transform = view_transform(from, to, up);
	return (0);
}
