/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokerjea <rokerjea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:40:49 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/12 16:06:56 by rokerjea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_rgb	create_color(float red, float green, float blue)
{
	t_rgb	color;

	color.x = red;
	color.y = green;
	color.z = blue;
	color.w = 0;
	return (color);
}

/* intersect the world with the given ray
and return the color at the given intersection */
t_rgb	color_at(t_scene *world, t_ray ray)
{
	t_inter	i;
	t_rgb	color;

	i = intersect_world(world, ray);
	if (i.t <= 0)
		return ((t_rgb)BLACK);
	prepare_computations(&i, ray);
	color = shade_hit(world, i);
	return (color);
}
