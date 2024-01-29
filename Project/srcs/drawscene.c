/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawscene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjeiwjifeoh <fjeiwjifeoh@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:10:19 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/15 23:06:40 by fjeiwjifeoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	drawscene(t_scene *scene, t_img *img)
{
	size_t		x;
	size_t		y;
	t_ray		r;
	t_rgb		color;

	y = 0;
	while (y < scene->cam->vsize)
	{
		x = 0;
		while (x < scene->cam->hsize)
		{
			r = ray_for_pixel(*(scene->cam), x, y);
			color = color_at(scene, r);
			my_mlx_pixel_put(img, x, y, rgbvtoi(color));
			x++;
		}
		y++;
	}
	printf("finish\n\n");
}
