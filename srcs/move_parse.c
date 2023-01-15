/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:31:58 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/15 22:41:43 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user_input.h"

bool	click_hits(t_scene *scene, int x, int y)
{
	t_ray	r;
	t_inter	i;

	r = ray_for_pixel(*(scene->cam), x, y);
	i = intersect_world(scene, r);
	if (i.t < 0)
		return (0);
	scene->move.obj = i.obj;
	return (1);
}

int	mouse_click(int keycode, int x, int y, t_scene *scene)
{
	if (!scene->objs)
		return (0);
	if (keycode == LEFT_CLICK)
	{
		if (click_hits(scene, x, y))
		{
			scene->move.asked = 1;
			printf("object selected\nchoose your move/change:\n");
			printf("\t-translation (t)\n");
			printf("\t-rotation (r) (except for spheres)\n");
			printf("\t-resize (s)\n\n");
		}
	}
	else
	{
		if (scene->move.asked)
			printf("\ncancelled\n");
		ft_bzero(&scene->move, sizeof(t_move));
	}
	return (0);
}

void	move_parse(t_scene *scene, int keycode)
{
	if (is_id_key(keycode))
	{
		scene->move.id = keycode;
		if (scene->move.id == 's')
			printf("s selected. please choose the value\n");
		else
			printf("%c selected. please choose the axis x, y or z\n", keycode);
	}
	else if (scene->move.asked && scene->move.id && is_axis_key(keycode))
	{
		scene->move.axis = keycode;
		printf("%c selected. choose value btw -9 & 9 units\n", keycode);
	}
	else if (scene->move.asked && scene->move.id
		&& (scene->move.axis || scene->move.id == 's')
		&& keycode == '-')
		scene->move.neg = '-';
	else if (scene->move.asked && scene->move.id
		&& (scene->move.axis || scene->move.id == 's')
		&& is_value_key(keycode))
	{
		scene->move.value = keycode - 48;
		if (scene->move.neg)
			scene->move.value = -scene->move.value;
		printf("%c%c chosen\n", scene->move.neg, keycode);
		scene->move.neg = 0;
		handle_obj_move(scene);
	}
}