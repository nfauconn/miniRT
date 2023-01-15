/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:31:58 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/15 19:47:21 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user_input.h"

bool	is_value_key(int keycode)
{
	return (keycode >= '0' && keycode <= '9');
}

bool	is_axis_key(int keycode)
{
	return (keycode == 'x' || keycode == 'y' || keycode == 'z');
}

bool	is_id_key(int keycode)
{
	return (keycode == 'r' || keycode == 't' || keycode == 's');
}

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
			scene->move.cam = NULL;
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
