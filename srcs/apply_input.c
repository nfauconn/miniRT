/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:39:47 by fjeiwjifeoh       #+#    #+#             */
/*   Updated: 2023/01/13 15:38:01 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user_input.h"

bool	rotate_obj(t_elem *obj, int keycode)
{
	if (obj->shape == sphere)
		return (1);
	if (keycode == W_KEY)
		obj->orientation.x += 0.01;
	else if (keycode == S_KEY)
		obj->orientation.x -= 0.01;
	else if (keycode == A_KEY)
		obj->orientation.z += 0.01;
	else if (keycode == D_KEY)
		obj->orientation.z -= 0.01;
	printf("rotating...\n");
	return (0);
}

bool	resize_obj(t_elem *obj, int keycode)
{
	if (obj->shape == plane)
		return (1);
	if (keycode == '=')
	{
		if (obj->shape == sphere)
			obj->specs.radius += 0.1;
		else if (obj->shape == cylinder)
		{
			obj->specs.diam_hght[0] += 0.1;
			obj->specs.diam_hght[1] += 0.1;
		}
	}
	else if (keycode == '-')
	{
		if (obj->shape == sphere)
			obj->specs.radius -= 0.1;
		else if (obj->shape == cylinder)
		{
			obj->specs.diam_hght[0] -= 0.1;
			obj->specs.diam_hght[1] -= 0.1;
		}
	}
	printf("resizing...\n");
	return (0);
}

bool	translate_obj(t_elem *obj, int keycode)
{
	if (keycode == UP_ARROW)
		obj->w_pos.y += 0.1;
	else if (keycode == DOWN_ARROW)
		obj->w_pos.y -= 0.1;
	else if (keycode == LEFT_ARROW)
		obj->w_pos.x -= 0.1;
	else if (keycode == RIGHT_ARROW)
		obj->w_pos.x += 0.1;
	printf("translating...\n");
	return (0);
}

bool	change_obj(t_elem *obj, int keycode)
{
	if (is_translate(keycode))
		return (translate_obj(obj, keycode));
	else if (is_rotate(keycode))
		return (rotate_obj(obj, keycode));
	else if (keycode == '=' || keycode == '-')
		return (resize_obj(obj, keycode));
	return (1);
}

void	handle_move(t_scene *scene, int keycode)
{
	if (change_obj(scene->move.obj, keycode))
		return ;
	change_obj_transform_matr(scene->move.obj);
	drawscene(scene, scene->img);
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img->ptr, 0, 0);
}
