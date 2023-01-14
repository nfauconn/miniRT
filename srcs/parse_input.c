/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:31:58 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/14 14:28:43 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user_input.h"

bool	is_rotate(int keycode)
{
	return (keycode == W_KEY || keycode == A_KEY
		|| keycode == S_KEY || keycode == D_KEY);
}

bool	is_translate(int keycode)
{
	return (keycode >= LEFT_ARROW && keycode <= DOWN_ARROW);
}

bool	is_valid_key(int keycode)
{
	return ((keycode >= LEFT_ARROW && keycode <= DOWN_ARROW) || keycode == W_KEY
		|| keycode == A_KEY || keycode == S_KEY || keycode == D_KEY
		|| keycode == '=' || keycode == '-');
}

bool	click_hits(t_scene *scene, int x, int y)
{
	t_ray	r;
	t_inter	i;

	r = ray_for_pixel(*(scene->cam), x, y);
	i = intersect_world(scene, r);
	if (i.t < 0)
		return (0);
	scene->move.asked = 1;
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
			printf("\nobject selected\n");
	}
	else
	{
		if (scene->move.asked)
			printf("object unselected\n");
		scene->move.asked = 0;
		scene->move.obj = NULL;
	}
	return (0);
}
