/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 18:41:43 by nfauconn          #+#    #+#             */
/*   Updated: 2022/12/14 17:16:32 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/* //aspect is the aspect ratio, like 16:9
void	setup_camera(t_scene *scene, t_elem *cam)
{
	float		half_view;
	float		aspect;

	cam->transform = identity_matr();
	half_view = tan(fov / 2);
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
} */

/* static t_m4x4_f	cam_transf(t_camera *cam)
{
	t_point		from; //r.orig?
	t_point		to; //r.dest ?
	t_point		up;
	t_m4x4_f	tranf;

	from = cam->w_pos;
	to = //position(ray, t) = from + to * t;
	up = create_vector(0, 1, 0);
	transf = view_transform(from, to, up);
	return (transf);
} */

void	setup_camera(t_camera *cam, float hsize, float vsize)
{
	float		half_view;
	float		aspect;

	cam->hsize = hsize;
	cam->vsize = vsize;
	cam->transform = identity_matr();
/* 	cam->transform = cam_transf(cam); */
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