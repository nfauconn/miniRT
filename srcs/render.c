/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 13:29:20 by nfauconn          #+#    #+#             */
/*   Updated: 2023/01/07 13:29:22 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	render(t_scene *scene, t_img *img)
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
	printf("finish\n");
}

