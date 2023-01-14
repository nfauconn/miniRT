/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:39:47 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/14 17:39:15 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user_input.h"

bool	rotate_obj(t_elem *obj, int dir_key, int size)
{
	if (obj->shape == sphere)
		return (1);
	if (dir_key == W_KEY)
		obj->orientation.x += 0.1 * size;
	else if (dir_key == S_KEY)
		obj->orientation.x -= 0.1 * size;
	else if (dir_key == A_KEY)
		obj->orientation.z += 0.1 * size;
	else if (dir_key == D_KEY)
		obj->orientation.z -= 0.1 * size;
	printf("rotating by %d units...\n", size);
	return (0);
}

bool	resize_obj(t_elem *obj, int dir_key, int size)
{
	if (obj->shape == plane)
		return (1);
	if (dir_key == '=')
	{
		if (obj->shape == sphere)
			obj->specs.radius += 0.01 * size;
		else if (obj->shape == cylinder)
		{
			obj->specs.diam_hght[0] += 0.01 * size;
			obj->specs.diam_hght[1] += 0.01 * size;
		}
	}
	else if (dir_key == '-')
	{
		if (obj->shape == sphere)
			obj->specs.radius -= 0.01 * size;
		else if (obj->shape == cylinder)
		{
			obj->specs.diam_hght[0] -= 0.01 * size;
			obj->specs.diam_hght[1] -= 0.01 * size;
		}
	}
	printf("resizing by %d units...\n", size);
	return (0);
}

bool	translate_obj(t_elem *obj, int dir_key, int size)
{
	if (dir_key == UP_ARROW)
		obj->w_pos.y += 0.1 * size;
	else if (dir_key == DOWN_ARROW)
		obj->w_pos.y -= 0.1 * size;
	else if (dir_key == LEFT_ARROW)
		obj->w_pos.x -= 0.1 * size;
	else if (dir_key == RIGHT_ARROW)
		obj->w_pos.x += 0.1 * size;
	printf("translating by %d units...\n", size);
	return (0);
}

bool	change_obj(t_elem *obj, int dir_key, int size)
{
	if (is_translate(dir_key))
		return (translate_obj(obj, dir_key, size));
	else if (is_rotate(dir_key))
		return (rotate_obj(obj, dir_key, size));
	else if (dir_key == '=' || dir_key == '-')
		return (resize_obj(obj, dir_key, size));
	return (1);
}

void	handle_move(t_scene *scene, int dir_key, int size)
{
	if (change_obj(scene->move.obj, dir_key, size))
		return ;
	change_obj_transform_matr(scene->move.obj);
	drawscene(scene, scene->img);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img->ptr, 0, 0);
}
