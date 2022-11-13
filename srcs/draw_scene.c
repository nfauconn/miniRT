/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfauconn <nfauconn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:10:19 by nfauconn          #+#    #+#             */
/*   Updated: 2022/11/13 19:47:00 by nfauconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	position(t_point point, t_vector direction, float magnitude)
{
	return (point + direction * magnitude);
}

int	get_background_color(int x, int y, t_scene *scene)
{
	t_vector	ray_direction;
	int			color;
	float		u = x / (float)WIDTH;
	float		v = y / (float)HEIGHT;
	
	return (color);
}

void	draw_scene(t_img *img, t_scene *scene)
{
	int			color;
	size_t		x;
	size_t		y;
	float		pixels = WIDTH * HEIGHT;
	float		pixel_size_x = WIDTH / pixels;
	float		pixel_size_y = HEIGHT / pixels;
	float		half_x = WIDTH / 2;
	float		half_y = HEIGHT / 2;
	float		world_x;
	float		world_y;
	t_point		position;
	t_vector	ray;
	float		wall_z = 10;
	t_point		ray_origin = {0, 0, -5}

	y = 0;
	while (y < HEIGHT)
	{
		world_y = pixel_size_y * y - half_y; // compute the world y coordinate (top = +half, bottom = -half)
		x = 0;
		while (x < WIDTH)
		{
			world_x = pixel_size_x * x - half_x;
			position = {world_x, world_y, wall_z};
			ray = unit_direction(position - ray_origin);
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}