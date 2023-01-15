/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_apply_cam.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 15:57:36 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/15 20:57:10 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user_input.h"

static bool	rotate_cam(t_scene *scene)
{
	scene->move.value *= 0.1;
	if (scene->move.axis == 'x')
		scene->move.cam->orientation.x += scene->move.value;
	else if (scene->move.axis == 'y')
		scene->move.cam->orientation.y += scene->move.value;
	else if (scene->move.axis == 'z')
		scene->move.cam->orientation.z += scene->move.value;
	return (0);
}

static bool	translate_cam(t_scene *scene)
{
	if (scene->move.axis == 'x')
		scene->move.cam->w_pos.x += scene->move.value;
	if (scene->move.axis == 'y')
		scene->move.cam->w_pos.y += scene->move.value;
	if (scene->move.axis == 'z')
		scene->move.cam->w_pos.z += scene->move.value;
	return (0);
}

static bool	change_cam(t_scene *scene)
{
	if (scene->move.id == 't')
		return (translate_cam(scene));
	else if (scene->move.id == 'r')
		return (rotate_cam(scene));
	return (1);
}

void	handle_cam_move(t_scene *scene)
{
	if (change_cam(scene))
		return ;
	change_cam_transform_matr(scene->move.cam);
	drawscene(scene, scene->img);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img->ptr, 0, 0);
}
