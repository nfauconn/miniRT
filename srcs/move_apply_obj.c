/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_apply_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:39:47 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/15 20:13:07 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user_input.h"

bool	rotate_obj(t_scene *scene)
{
	if (scene->move.obj->shape == sphere)
		return (error_display("sphere wont rotate visibly\n"));
	if (scene->move.axis == 'x')
		scene->move.obj->orientation.x += scene->move.value;
	else if (scene->move.axis == 'y')
		scene->move.obj->orientation.y += scene->move.value;
	else if (scene->move.axis == 'z')
		scene->move.obj->orientation.z += scene->move.value;
	return (0);
}

bool	resize_obj(t_scene *scene)
{
	if (scene->move.obj->shape == plane)
		return (error_display("plane dont have a size to change\n"));
	if (scene->move.obj->shape == sphere)
		scene->move.obj->specs.radius += scene->move.value;
	else if (scene->move.obj->shape == cylinder)
	{
		scene->move.obj->specs.diam_hght[0] += scene->move.value;
		scene->move.obj->specs.diam_hght[1] += scene->move.value;
	}
	return (0);
}

bool	translate_obj(t_scene *scene)
{
	if (scene->move.axis == 'x')
		scene->move.obj->w_pos.x += scene->move.value;
	if (scene->move.axis == 'y')
		scene->move.obj->w_pos.y += scene->move.value;
	if (scene->move.axis == 'z')
		scene->move.obj->w_pos.z += scene->move.value;
	return (0);
}

bool	change_obj(t_scene *scene)
{
	if (scene->move.id == 't')
		return (translate_obj(scene));
	else if (scene->move.id == 'r')
		return (rotate_obj(scene));
	else if (scene->move.id == 's')
		return (resize_obj(scene));
	return (1);
}

void	handle_obj_move(t_scene *scene)
{
	if (change_obj(scene))
		return ;
	change_obj_transform_matr(scene->move.obj);
	drawscene(scene, scene->img);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img->ptr, 0, 0);
}
